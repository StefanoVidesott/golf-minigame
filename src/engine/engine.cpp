#include "engine.hpp"

namespace Engine {

    Engine::Engine() {
        this->window = new sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Golf-Minigame");
        this->window->setVerticalSyncEnabled(true);
        this->window->setFramerateLimit(144);
    }

    Engine::~Engine() {
        delete window;
        if (!scenes.empty()) {
            std::unordered_set<Scene::Scene*> deleted;
            while (!scenes.empty()) {
                Scene::Scene* s = scenes.top();
                if (!deleted.count(s)) {
                    delete s;
                    deleted.insert(s);
                }
                scenes.pop();
            }
        }
    }

    void Engine::LoadScene(Scene::Scene *scene) {
        if (scene) {
            scene->Start();
            this->scenes.push(scene);
            scene->loaded = true;
            scene->active = true;
            scene->window = this->window;
            if (this->currentScene) {
                this->currentScene->active = false;
            }
            this->currentScene = scene;
        }
    }

    void Engine::DropScene() {
        if (currentScene) {
            currentScene->active = false;
            delete scenes.top();
            scenes.pop();
            if (!scenes.empty()) {
                currentScene = scenes.top();
                currentScene->active = true;
            } else {
                currentScene = nullptr;
            }
        }
    }

    void Engine::Start() {
        ResourceManager::ResourceManager::loadFont("DefaultFont", "./src/engine/res/font/CreatoDisplay-Regular.otf");
    }

    void Engine::Run() {
        this->Start();
        this->Update();
    }

    void Engine::Update() {
        while (this->window->isOpen())
        {
            if(currentScene) {
                this->deltaTime = this->deltaClock.restart().asSeconds();
                this->currentScene->Update(this->deltaTime);

                for (const auto& entity : this->currentScene->entities)
                {
                    if (entity) {
                        entity->Update(this->deltaTime);
                    }
                }

                while (const std::optional event = this->window->pollEvent())
                {
                    if (event->is<sf::Event::Closed>())
                    {
                        std::cout << "Closing window..." << std::endl;
                        this->window->close();
                    }
                    else if (const auto* resized = event->getIf<sf::Event::Resized>())
                    {
                        // update the view to the new size of the window
                        sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized->size));
                        this->window->setView(sf::View(visibleArea));
                    }
                    this->currentScene->HandleEvent(event);
                }

                this->window->clear();
                this->currentScene->Render();
                for (const auto& entity : this->currentScene->entities)
                {
                    if (entity) {
                        entity->Render(this->window);
                    }
                }
                this->window->display();
            }
            else {
                while (const std::optional event = this->window->pollEvent())
                {
                    if (event->is<sf::Event::Closed>())
                    {
                        this->window->close();
                    }
                }
                this->window->clear();
                this->window->display();
            }
        }
    }
}
