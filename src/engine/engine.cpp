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
    }

    void Engine::LoadScene(std::unique_ptr<Scene::Scene> scene) {
        if (scene) {
            scene->Start();
            scene->active = true;
            scene->window = this->window;
            if (!this->scenes.empty()) {
                this->scenes.top()->active = false;
            }
            this->scenes.push(std::move(scene));
        }
    }

    void Engine::DropScene() {
        if (!this->scenes.empty()) {
            this->scenes.top()->active = false;
            this->scenes.pop();
            if (!this->scenes.empty()) {
                this->scenes.top()->active = true;
            }
        }
    }

    void Engine::Start() {
        std::unique_ptr<OverlayScene::DebugOverlayScene> debugOverlay = std::make_unique<OverlayScene::DebugOverlayScene>();
        debugOverlay->Start();

        this->overlays.push_back(std::move(debugOverlay));
    }

    void Engine::InitResources() {
        ResourceManager::ResourceManager::SetWindow(this->window);

        ResourceManager::ResourceManager::SetInputManager(&this->inputManager);
        ResourceManager::ResourceManager::sceneManager.Initialize(&this->scenes, &this->overlays);

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

            if(!this->scenes.empty()) {
                if (this->scenes.top() && this->scenes.top()->active) {
                    this->scenes.top()->HandleEvent(event);
                }
            }

            for(std::unique_ptr<Scene::Scene>& overlay : this->overlays) {
                overlay->HandleEvent(event);
            }
        }
    }

    void Engine::Update() {
        this->deltaTime = this->deltaClock.restart().asSeconds();
        if(!this->scenes.empty()) {
            if (this->scenes.top() && this->scenes.top()->active) {
                this->scenes.top().get()->Update(this->deltaTime);
            }
        }

        for(std::unique_ptr<Scene::Scene>& overlay : this->overlays) {
            if (overlay) {
                overlay->Update(this->deltaTime);
            }
        }
    }

    void Engine::Render() {
        this->window->clear();

        if (!this->scenes.empty()) {
            if (this->scenes.top()->visible) {
                this->scenes.top()->Render();
            }
        }
        for(const std::unique_ptr<Scene::Scene>& overlay : this->overlays) {
            if (overlay && overlay->visible) {
                overlay->Render();
            }
        }

        this->window->display();
    }

} // namespace Engine
