#include "engine.hpp"

namespace Engine {

    Engine::Engine(sf::VideoMode mode, const std::string& title, unsigned int style, std::function<void()> loadApplicationResources){
        this->loadApplicationResources = loadApplicationResources;

        ResourceManager::ResourceManager::SetTextureManager(&this->textureManager);
        ResourceManager::ResourceManager::SetFontManager(&this->fontManager);
        ResourceManager::ResourceManager::SetAudioManager(&this->audioManager);
        ResourceManager::ResourceManager::SetSceneManager(&this->sceneManager);
        ResourceManager::ResourceManager::SetInputManager(&this->inputManager);
        ResourceManager::ResourceManager::SetSettingsManager(&this->settingsManager);

        this->InitResources();

        this->window = std::make_unique<sf::RenderWindow>(mode, title, style);
        ResourceManager::ResourceManager::SetWindow(this->window.get());

        this->settingsManager.LoadSettings();
    }

    Engine::~Engine() {
        this->scenes = std::stack<std::unique_ptr<Scene::Scene>>();
        this->overlays.clear();
        this->window.reset();
    }

    void Engine::LoadScene(std::unique_ptr<Scene::Scene> scene) {
        if (scene) {
            scene->SetActive(true);
            scene->SetWindow(this->window.get());

            if (!this->scenes.empty()) {
                this->scenes.top()->SetActive(false);
            }

            scene->Start();
            this->scenes.push(std::move(scene));
        }
    }

    void Engine::DropScene() {
        if (!this->scenes.empty()) {
            this->scenes.top()->SetActive(false);
            this->scenes.pop();
            if (!this->scenes.empty()) {
                this->scenes.top()->SetActive(true);
                this->scenes.top()->PlaceEntities();
            }
        }
    }

    void Engine::Start() {
        std::unique_ptr<OverlayScene::DebugOverlayScene> debugOverlay = std::make_unique<OverlayScene::DebugOverlayScene>();
        debugOverlay->Start();

        this->overlays.push_back(std::move(debugOverlay));
    }

    void Engine::InitResources() {
        this->sceneManager.Initialize(&this->scenes, &this->overlays,
            [this](std::unique_ptr<Scene::Scene> scene) { this->LoadScene(std::move(scene)); },
            [this]() { this->DropScene(); }
        );

        this->fontManager.LoadFont("DefaultFont", "src/engine/res/font/CreatoDisplay-Regular.otf");
        this->textureManager.LoadTexture("DefaultTexture", "src/engine/res/gfx/templategrid_orm.png");
        this->loadApplicationResources();
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
                if (this->scenes.top() && this->scenes.top()->IsActive()) {
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
            if (this->scenes.top() && this->scenes.top()->IsActive()) {
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
            if (this->scenes.top() && this->scenes.top()->IsVisible()) {
                this->scenes.top()->Render();
            }
        }
        for(const std::unique_ptr<Scene::Scene>& overlay : this->overlays) {
            if (overlay && overlay->IsVisible()) {
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
