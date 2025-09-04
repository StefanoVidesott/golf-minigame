#include "settings_scene.hpp"

namespace ApplicationScene {

    void SettingsScene::Start() {
        this->inputManager = Engine::ResourceManager::ResourceManager::GetInputManager();
        this->settingsManager = Engine::ResourceManager::ResourceManager::GetSettingsManager();

        // Create Background Entity
        std::unique_ptr<Engine::Entity> bgPtr = std::make_unique<Engine::Entity>();
        this->bg = bgPtr.get();
        Engine::Components::SpriteComponent *bgSpriteComponent = new Engine::Components::SpriteComponent(Engine::ResourceManager::ResourceManager::GetTextureManager()->GetTexture("background"));
        bgPtr->AddComponent("BackgroundSprite", std::unique_ptr<Engine::Components::Component>(bgSpriteComponent));

        // Create Resolution section
        std::unique_ptr<Engine::Entity> resolutionTextPtr = std::make_unique<Engine::Entity>();
        this->resolutionText = resolutionTextPtr.get();
        Engine::Components::TextComponent *resolutionTextComponent = new Engine::Components::TextComponent("GameFont", "Window Resolution:", 28);
        resolutionTextComponent->SetOrigin(sf::Vector2f(0, resolutionTextComponent->GetGlobalBounds().size.y/2));
        resolutionTextComponent->SetOutlineColor(sf::Color::Black);
        resolutionTextComponent->SetOutlineThickness(2.f);
        resolutionTextPtr->AddComponent("Text", std::unique_ptr<Engine::Components::Component>(resolutionTextComponent));

        this->resolutionDropdown = new Engine::Entities::Dropdown(
            {"1600x1200", "1280x960", "960x720", "640x480"},
            this->ActualResolution(),
            "GameFont",
            20,
            sf::Vector2f(20, 15)
        );
        this->resolutionDropdown->SetOnSelectionChanged(
            [this](const std::string& res) { UpdateResolution(res); }
        );
        this->resolutionDropdown->SetButtonTexture(Engine::ResourceManager::ResourceManager::GetTextureManager()->GetTexture("tile64_light"));
        this->resolutionDropdown->SetButtonColors({255, 255, 255}, {200, 200 ,200}, {150 ,150 ,150});

        // Create vsync section
        std::unique_ptr<Engine::Entity> vsyncTextPtr = std::make_unique<Engine::Entity>();
        this->vsyncText = vsyncTextPtr.get();
        Engine::Components::TextComponent *vsyncTextComponent = new Engine::Components::TextComponent("GameFont", "Vertical Sync:", 28);
        vsyncTextComponent->SetOrigin(sf::Vector2f(0, vsyncTextComponent->GetGlobalBounds().size.y/2));
        vsyncTextComponent->SetOutlineColor(sf::Color::Black);
        vsyncTextComponent->SetOutlineThickness(2.f);
        vsyncTextPtr->AddComponent("Text", std::unique_ptr<Engine::Components::Component>(vsyncTextComponent));

        std::unique_ptr<Engine::Entities::TextButton> vsyncButtonPtr = std::make_unique<Engine::Entities::TextButton>(ActualVSyncState(), [this]() { this->OnVSyncButtonClick(); }, "GameFont", 30);
        this->vsyncButton = vsyncButtonPtr.get();
        vsyncButtonPtr->SetBackgroundTexture(Engine::ResourceManager::ResourceManager::GetTextureManager()->GetTexture("tile64_light"));
        vsyncButtonPtr->SetBackgroundColors({255, 255, 255}, {200, 200 ,200}, {150 ,150 ,150});

        this->entities.push_back(std::move(bgPtr));
        this->entities.push_back(std::move(resolutionTextPtr));
        this->entities.push_back(std::unique_ptr<Engine::Entity>(this->resolutionDropdown));
        this->entities.push_back(std::move(vsyncTextPtr));
        this->entities.push_back(std::move(vsyncButtonPtr));

        this->PlaceEntities();
    }

    void SettingsScene::PlaceEntities() {
        sf::Vector2u bgSize = Engine::ResourceManager::ResourceManager::GetTextureManager()->GetTexture("background").getSize();
        sf::Vector2u windowSize = this->window->getSize();
        sf::Vector2f scaleFactor = sf::Vector2f(static_cast<float>(windowSize.x) / bgSize.x, static_cast<float>(windowSize.y) / bgSize.y);

        this->bg->GetTransform()->SetScale(scaleFactor);

        this->resolutionText->GetTransform()->SetScale(scaleFactor);
        this->resolutionText->GetTransform()->SetPosition(sf::Vector2f(75*scaleFactor.x, 120*scaleFactor.y));
        this->resolutionDropdown->SetScale(scaleFactor);
        this->resolutionDropdown->SetPosition(sf::Vector2f(460 * scaleFactor.x, 130 * scaleFactor.y));

        this->vsyncText->GetTransform()->SetScale(scaleFactor);
        this->vsyncText->GetTransform()->SetPosition(sf::Vector2f(75*scaleFactor.x, 220*scaleFactor.y));
        this->vsyncButton->GetTransform()->SetScale(scaleFactor);
        this->vsyncButton->GetTransform()->SetPosition(sf::Vector2f(460 * scaleFactor.x, 215 * scaleFactor.y));
    }

    void SettingsScene::UpdateBehavior(float deltaTime) {
    }

    void SettingsScene::HandleEvent(const std::optional<sf::Event>& event) {
        if(this->inputManager) {
            if(this->inputManager->IsKeyPressed(sf::Keyboard::Key::Escape)) {
                Engine::ResourceManager::ResourceManager::GetSceneManager()->DropScene();
            }
        }
    }

    void SettingsScene::RenderBehavior() {
        this->resolutionDropdown->RenderCustomBehavior(this->window);
    }

    std::string SettingsScene::GetName() const {
        return "SettingsScene";
    }

    void SettingsScene::UpdateResolution(const std::string& resolution) {
        size_t xpos = resolution.find('x');
        if (xpos == std::string::npos) {
            return;
        }
        int width = std::stoi(resolution.substr(0, xpos));
        int height = std::stoi(resolution.substr(xpos + 1));

        Engine::ResourceManager::SettingsManager* settingsManager = Engine::ResourceManager::ResourceManager::GetSettingsManager();
        settingsManager->Set("window_width", width);
        settingsManager->Set("window_height", height);
        settingsManager->ApplyWindowSize();
        settingsManager->SaveSettings();

        if (this->window) {
            this->window->setSize({static_cast<unsigned int>(width), static_cast<unsigned int>(height)});
            this->PlaceEntities();
        }
    }

    void SettingsScene::OnVSyncButtonClick() {
        bool vsync = this->settingsManager->Get<bool>("vsync", false);
        vsync = !vsync;
        this->settingsManager->Set("vsync", vsync);
        this->settingsManager->ApplyVideoSettings();
        this->settingsManager->SaveSettings();

        this->vsyncButton->SetTextString(ActualVSyncState());
    }

    std::string SettingsScene::ActualResolution() const {
        int width = this->settingsManager->Get<int>("window_width", 1280);
        int height = this->settingsManager->Get<int>("window_height", 720);
        return (std::to_string(width) + "x" + std::to_string(height));
    }

    std::string SettingsScene::ActualVSyncState() const {
        bool vsync = this->settingsManager->Get<bool>("vsync", false);
        return vsync ? "On" : "Off";
    }

} // namespace ApplicationScene
