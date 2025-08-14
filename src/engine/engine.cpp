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

        this->debugOverlay = new OverlayScene::DebugOverlayScene();
        this->debugOverlay->Start();
        this->debugOverlay->active = true;
        this->debugOverlay->window = this->window;
        this->debugOverlay->currentScene = &this->currentScene;
        this->debugOverlay->engine_scenes = &this->scenes;
        this->debugOverlay->engine_overlays = &this->overlays;

        this->overlays.push_back(this->debugOverlay);
    }

    void Engine::Run() {
        this->Start();

        while (this->window->isOpen())
        {
            this->HandleEvents();
            this->Update();
            this->Render();
        }
    }

    void Engine::HandleEvents() {
        this->input.Update();
        while (const std::optional event = this->window->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                this->window->close();
            }
            else if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized->size));
                this->window->setView(sf::View(visibleArea));
            }
            this->input.HandleEvents(*event);
            this->currentScene->HandleEvent(event);
        }
    }

    void Engine::Update() {
        this->deltaTime = this->deltaClock.restart().asSeconds();
        this->currentScene->Update(this->deltaTime);

        for (std::unique_ptr<Entity>& entity : this->currentScene->entities)
        {
            if (entity) {
                entity->Update(this->deltaTime);
            }
        }

        for(Scene::Scene* overlay : this->overlays) {
            overlay->Update(this->deltaTime);
        }

        for(Scene::Scene* overlay : this->overlays) {
            for (std::unique_ptr<Entity>& entity : overlay->entities)
            {
                if (entity) {
                    entity->Update(this->deltaTime);
                }
            }
        }

    }

    void Engine::Render() {
        this->window->clear();
        this->currentScene->Render();

        for (std::unique_ptr<Entity>& entity : this->currentScene->entities)
        {
            if (entity) {
                entity->Render(this->window);
            }
        }

        for(Scene::Scene* overlay : this->overlays) {
            for (std::unique_ptr<Entity>& entity : overlay->entities)
            {
                if (entity) {
                    entity->Render(this->window);
                }
            }
        }

        for(Scene::Scene* overlay : this->overlays) {
            overlay->Render();
        }

        this->window->display();
    }

} // namespace Engine
