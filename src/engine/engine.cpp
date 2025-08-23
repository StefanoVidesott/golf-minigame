#include "engine.hpp"

namespace Engine {

    Engine::Engine(sf::VideoMode mode, const std::string& title, unsigned int style) {
        this->window = std::make_unique<sf::RenderWindow>(mode, title, style);
        // this->window->setVerticalSyncEnabled(true);
        // this->window->setFramerateLimit(144);
        this->InitResources();
    }

    Engine::~Engine() {
        this->scenes = std::stack<std::unique_ptr<Scene::Scene>>();
        this->overlays.clear();
        this->window.reset();
    }

    void Engine::LoadScene(std::unique_ptr<Scene::Scene> scene) {
        if (scene) {
            scene->active = true;
            scene->window = this->window.get();
            if (!this->scenes.empty()) {
                this->scenes.top()->active = false;
            }
            scene->Start();
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
        ResourceManager::ResourceManager::SetWindow(this->window.get());

        ResourceManager::ResourceManager::SetInputManager(&this->inputManager);
        ResourceManager::ResourceManager::sceneManager.Initialize(&this->scenes, &this->overlays);

        ResourceManager::ResourceManager::LoadFont("DefaultFont", "./src/engine/res/font/CreatoDisplay-Regular.otf");
        ResourceManager::ResourceManager::LoadTexture("DefaultTexture", "./src/engine/res/gfx/templategrid_orm.png");
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
        while (std::optional<sf::Event> event = this->window->pollEvent())
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
            if (this->scenes.top() && this->scenes.top()->visible) {
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

    void Engine::SetWindowPosition(const sf::Vector2i& position) {
        if (this->window) {
            this->window->setPosition(position);
        }
    }

} // namespace Engine
