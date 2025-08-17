#include "engine.hpp"

namespace Engine {

    Engine::Engine() {
        this->window = new sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Golf-Minigame");
        // this->window->setVerticalSyncEnabled(true);
        // this->window->setFramerateLimit(144);
        this->InitResources();
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
        for (Scene::Scene* overlay : this->overlays) {
            delete overlay;
        }
    }

    void Engine::LoadScene(Scene::Scene *scene) {
        if (scene) {
            scene->Start();
            this->scenes.push(scene);
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
        OverlayScene::DebugOverlayScene *debugOverlay = new OverlayScene::DebugOverlayScene();
        debugOverlay->Start();

        this->overlays.push_back(debugOverlay);
    }

    void Engine::InitResources() {
        ResourceManager::ResourceManager::SetWindow(this->window);

        ResourceManager::ResourceManager::SetInputManager(&this->inputManager);
        ResourceManager::ResourceManager::sceneManager.Initialize(&this->scenes, &this->overlays, &this->currentScene);

        ResourceManager::ResourceManager::loadFont("DefaultFont", "./src/engine/res/font/CreatoDisplay-Regular.otf");
        ResourceManager::ResourceManager::loadTexture("DefaultTexture", "./src/engine/res/gfx/templategrid_orm.png");
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
        this->inputManager.Update();
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

            this->inputManager.HandleEvents(*event);

            if(this->currentScene) {
                if (this->currentScene->active) {
                    this->currentScene->HandleEvent(event);
                }
            }

            for(Scene::Scene* overlay : this->overlays) {
                overlay->HandleEvent(event);
            }
        }
    }

    void Engine::Update() {
        this->deltaTime = this->deltaClock.restart().asSeconds();
        if(this->currentScene) {
            if (this->currentScene->active) {
                this->currentScene->Update(this->deltaTime);
            }
        }

        for(Scene::Scene* overlay : this->overlays) {
            if (overlay) {
                overlay->Update(this->deltaTime);
            }
        }
    }

    void Engine::Render() {
        this->window->clear();

        if (this->currentScene) {
            if (this->currentScene->visible) {
                this->currentScene->Render();
            }
        }
        for(Scene::Scene* overlay : this->overlays) {
            if (overlay && overlay->visible) {
                overlay->Render();
            }
        }

        this->window->display();
    }

} // namespace Engine
