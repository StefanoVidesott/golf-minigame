#include "menu_scene.hpp"

namespace ApplicationScene {

    void MenuScene::Start() {
        // Create Background Entity
        std::unique_ptr<Engine::Entity> bgPtr = std::make_unique<Engine::Entity>();
        this->bg = bgPtr.get();
        Engine::Components::SpriteComponent *bgSpriteComponent = new Engine::Components::SpriteComponent(Engine::ResourceManager::ResourceManager::GetTextureManager()->GetTexture("background"));
        bgPtr->AddComponent("BackgroundSprite", std::unique_ptr<Engine::Components::Component>(bgSpriteComponent));
        this->entities.push_back(std::move(bgPtr));

        // Create Title Entity
        std::unique_ptr<Engine::Entity> titleEntityPtr = std::make_unique<Engine::Entity>();
        this->titleEntity = titleEntityPtr.get();
        Engine::Components::TextComponent *titleTextComponent = new Engine::Components::TextComponent("GameFont", "Gooolf!", 100);
        titleTextComponent->SetOrigin(sf::Vector2f(titleTextComponent->GetGlobalBounds().size.x/2, titleTextComponent->GetGlobalBounds().size.y/2));
        titleTextComponent->SetOutlineColor(sf::Color::Black);
        titleTextComponent->SetOutlineThickness(10.f);
        titleEntityPtr->AddComponent("TitleText", std::unique_ptr<Engine::Components::Component>(titleTextComponent));
        this->entities.push_back(std::move(titleEntityPtr));

        // Create Play Button
        this->playButton = new Engine::Entities::TextButton("Play", [this]() { this->OnPlayButtonClick(); }, "GameFont", 40);
        this->playButton->SetBackgroundTexture(Engine::ResourceManager::ResourceManager::GetTextureManager()->GetTexture("tile64_light"));
        this->playButton->SetBackgroundColors({255, 255, 255}, {200, 200 ,200}, {150 ,150 ,150});
        this->entities.push_back(std::unique_ptr<Engine::Entity>(this->playButton));

        // Create Settings Button
        this->settingsButton = new Engine::Entities::TextButton("Settings", [this]() { this->OnSettingsButtonClick(); }, "GameFont", 40);
        this->settingsButton->SetActionOnRelease(false);
        this->settingsButton->SetBackgroundTexture(Engine::ResourceManager::ResourceManager::GetTextureManager()->GetTexture("tile64_light"));
        this->settingsButton->SetBackgroundColors({255, 255, 255}, {200, 200 ,200}, {150 ,150 ,150});
        this->entities.push_back(std::unique_ptr<Engine::Entity>(this->settingsButton));
        this->PlaceEntities();
    }

    void MenuScene::PlaceEntities() {
        sf::Vector2u bgSize = Engine::ResourceManager::ResourceManager::GetTextureManager()->GetTexture("background").getSize();
        sf::Vector2u windowSize = this->window->getSize();
        sf::Vector2f scaleFactor = sf::Vector2f(static_cast<float>(windowSize.x) / bgSize.x, static_cast<float>(windowSize.y) / bgSize.y);

        this->bg->GetTransform()->SetScale(scaleFactor);
        this->titleEntity->GetTransform()->SetScale(scaleFactor);
        this->titleEntity->GetTransform()->SetPosition(sf::Vector2f(this->window->getSize().x/2, 100*scaleFactor.y));
        this->playButton->GetTransform()->SetScale(scaleFactor);
        this->playButton->GetTransform()->SetPosition(sf::Vector2f(this->window->getSize().x / 2, 270*scaleFactor.y));
        this->settingsButton->GetTransform()->SetScale(scaleFactor);
        this->settingsButton->GetTransform()->SetPosition(sf::Vector2f(this->window->getSize().x / 2, 360*scaleFactor.y));
    }

    void MenuScene::UpdateBehavior(float deltaTime) {
    }

    void MenuScene::HandleEvent(const std::optional<sf::Event>& event) {
    }

    void MenuScene::RenderBehavior() {
    }

    std::string MenuScene::GetName() const {
        return "MenuScene";
    }

    void MenuScene::OnPlayButtonClick() {
        Engine::ResourceManager::ResourceManager::GetSceneManager()->LoadScene(std::make_unique<GameScene>());
    }

    void MenuScene::OnSettingsButtonClick() {
        Engine::ResourceManager::ResourceManager::GetSceneManager()->LoadScene(std::make_unique<SettingsScene>());
    }

} // namespace Scene
