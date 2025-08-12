#include "engine.hpp"

namespace Engine {

    Engine::Engine() {
        this->window = new sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Golf-Minigame");
        this->window->setVerticalSyncEnabled(true);
        this->window->setFramerateLimit(144);
    }

    Engine::~Engine() {
        delete window;
        while (!scenes.empty()) {
            delete scenes.top();
            scenes.pop();
        }
        if (currentScene) {
            delete currentScene;
            currentScene = nullptr;
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
            this->scenes.pop();
            currentScene = this->scenes.top();
            currentScene->active = true;
        }
    }

    void Engine::Run() {
        this->Update();
    }

    void Engine::Update() {
        while (this->window->isOpen())
        {
            if(currentScene) {
                this->fixedDeltaTime = this->deltaClock.reset().asSeconds();
                this->currentScene->FixedUpdate(this->fixedDeltaTime);
                this->deltaTime = this->fixedDeltaTime + this->deltaClock.restart().asSeconds();
                this->currentScene->Update(this->deltaTime);

                while (const std::optional event = this->window->pollEvent())
                {
                    if (event->is<sf::Event::Closed>())
                    {
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

// Preserve ratio:

// else if (const auto* resizeEvent = event->getIf<sf::Event::Resized>()) {
//     float windowRatio = static_cast<float>(resizeEvent->size.x) / static_cast<float>(resizeEvent->size.y);
//     float targetRatio = 1920.f / 1080.f; // rapporto del gioco

//     sf::View view = this->window->getView();
//     if (windowRatio > targetRatio) {
//         float viewportWidth = targetRatio / windowRatio;
//         view.setViewport(sf::FloatRect(sf::Vector2f((1.f - viewportWidth) / 2.f, 0.f), sf::Vector2f(viewportWidth, 1.f)));
//     }
//     else {
//         float viewportHeight = windowRatio / targetRatio;
//         view.setViewport(sf::FloatRect(sf::Vector2f(0.f, (1.f - viewportHeight) / 2.f), sf::Vector2f(1.f, viewportHeight)));
//     }
//     this->window->setView(view);
// }
