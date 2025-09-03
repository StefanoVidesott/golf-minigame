#include "settings_scene.hpp"

namespace ApplicationScene {

    void SettingsScene::Start() {
        this->inputManager = Engine::ResourceManager::ResourceManager::GetInputManager();

        // Create Background Entity
        std::unique_ptr<Engine::Entity> bgPtr = std::make_unique<Engine::Entity>();
        this->bg = bgPtr.get();
        Engine::Components::SpriteComponent *bgSpriteComponent = new Engine::Components::SpriteComponent(Engine::ResourceManager::ResourceManager::GetTextureManager()->GetTexture("background"));
        bgPtr->AddComponent("BackgroundSprite", std::unique_ptr<Engine::Components::Component>(bgSpriteComponent));
        this->entities.push_back(std::move(bgPtr));

        // Create Resolution section
        std::unique_ptr<Engine::Entity> resolutionTextPtr = std::make_unique<Engine::Entity>();
        this->resolutionText = resolutionTextPtr.get();
        Engine::Components::TextComponent *resolutionTextComponent = new Engine::Components::TextComponent("GameFont", "Window resolution:", 28);
        resolutionTextComponent->SetOrigin(sf::Vector2f(0, resolutionTextComponent->GetGlobalBounds().size.y/2));
        resolutionTextComponent->SetOutlineColor(sf::Color::Black);
        resolutionTextComponent->SetOutlineThickness(2.f);
        resolutionTextPtr->AddComponent("TitleText", std::unique_ptr<Engine::Components::Component>(resolutionTextComponent));
        this->entities.push_back(std::move(resolutionTextPtr));

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

        this->entities.push_back(std::unique_ptr<Engine::Entity>(this->resolutionDropdown));

        this->PlaceEntities();
    }

    void SettingsScene::PlaceEntities() {
        sf::Vector2u bgSize = Engine::ResourceManager::ResourceManager::GetTextureManager()->GetTexture("background").getSize();
        sf::Vector2u windowSize = this->window->getSize();
        sf::Vector2f scaleFactor = sf::Vector2f(static_cast<float>(windowSize.x) / bgSize.x, static_cast<float>(windowSize.y) / bgSize.y);

        this->bg->GetTransform()->SetScale(scaleFactor);
        this->resolutionText->GetTransform()->SetScale(scaleFactor);
        this->resolutionText->GetTransform()->SetPosition(sf::Vector2f(100*scaleFactor.x, 130*scaleFactor.y));
        this->resolutionDropdown->SetScale(scaleFactor);
        Engine::Components::TextComponent* resolutionTextComponent = this->resolutionText->GetComponent<Engine::Components::TextComponent>("TitleText");
        this->resolutionDropdown->SetPosition(sf::Vector2f(resolutionTextComponent->GetGlobalBounds().position.x +resolutionTextComponent->GetGlobalBounds().size.x + 130 * scaleFactor.x, 130 * scaleFactor.y));
    }

    void SettingsScene::UpdateBehavior(float deltaTime) {
        this->resolutionDropdown->Update(deltaTime);
    }

    void SettingsScene::HandleEvent(const std::optional<sf::Event>& event) {
        if(this->inputManager) {
            if(this->inputManager->IsKeyPressed(sf::Keyboard::Key::Escape)) {
                Engine::ResourceManager::ResourceManager::GetSceneManager()->DropScene();
            }
        }
    }

    void SettingsScene::RenderBehavior() {
        this->resolutionDropdown->Render(this->window);
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

    std::string SettingsScene::ActualResolution() const {
        Engine::ResourceManager::SettingsManager* settingsManager = Engine::ResourceManager::ResourceManager::GetSettingsManager();
        int width = settingsManager->Get<int>("window_width", 1280);
        int height = settingsManager->Get<int>("window_height", 720);
        return (std::to_string(width) + "x" + std::to_string(height));
    }

} // namespace ApplicationScene
