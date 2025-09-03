#include "menu_scene.hpp"

namespace ApplicationScene {

    void MenuScene::Start() {
        // Initialize Resources
        this->inputManager = Engine::ResourceManager::ResourceManager::ResourceManager::GetInputManager();
        Engine::ResourceManager::ResourceManager::GetFontManager()->LoadFont("GameFont", "res/font/font.ttf");
        Engine::ResourceManager::ResourceManager::GetTextureManager()->LoadTexture("background", "res/gfx/bg.png");
        Engine::ResourceManager::ResourceManager::GetTextureManager()->LoadTexture("tile64_light", "res/gfx/tile64_light.png");

        Engine::ResourceManager::ResourceManager::GetAudioManager()->LoadMusic("BackgroundMusic", "res/music/bg_music.wav");
        Engine::ResourceManager::ResourceManager::GetAudioManager()->SetCurrentMusic("BackgroundMusic");
        Engine::ResourceManager::ResourceManager::GetAudioManager()->PlayMusic(); // TODO reactivate

        // Create Background Entity
        Engine::Entity *bg = new Engine::Entity();
        Engine::Components::SpriteComponent *bgSpriteComponent = new Engine::Components::SpriteComponent(Engine::ResourceManager::ResourceManager::GetTextureManager()->GetTexture("background"));
        bg->AddComponent("BackgroundSprite", std::unique_ptr<Engine::Components::Component>(bgSpriteComponent));
        sf::Vector2u bgSize = Engine::ResourceManager::ResourceManager::GetTextureManager()->GetTexture("background").getSize();
        sf::Vector2u windowSize = this->window->getSize();
        sf::Vector2f scaleFactor = sf::Vector2f(static_cast<float>(windowSize.x) / bgSize.x, static_cast<float>(windowSize.y) / bgSize.y);
        bg->GetTransform()->SetScale(scaleFactor);
        this->entities.push_back(std::unique_ptr<Engine::Entity>(bg));

        // Create Title Entity
        std::unique_ptr<Engine::Entity> titleEntity = std::make_unique<Engine::Entity>();
        Engine::Components::TextComponent *titleTextComponent = new Engine::Components::TextComponent("GameFont", "Gooolf!", 100);
        titleTextComponent->SetOrigin(sf::Vector2f(titleTextComponent->GetGlobalBounds().size.x/2, titleTextComponent->GetGlobalBounds().size.y/2));
        titleTextComponent->SetOutlineColor(sf::Color::Black);
        titleTextComponent->SetOutlineThickness(10.f);
        titleEntity->AddComponent("TitleText", std::unique_ptr<Engine::Components::Component>(titleTextComponent));
        titleEntity->GetTransform()->SetScale(scaleFactor);
        titleEntity->GetTransform()->SetPosition(sf::Vector2f(this->window->getSize().x/2, 100*scaleFactor.y));
        this->entities.push_back(std::move(titleEntity));

        // Create Play Button
        this->playButton = new Engine::Entities::TextButton("Play", [this]() { this->OnPlayButtonClick(); }, "GameFont", 40);
        this->playButton->SetBackgroundTexture(Engine::ResourceManager::ResourceManager::GetTextureManager()->GetTexture("tile64_light"));
        this->playButton->SetBackgroundColors(sf::Color::White, sf::Color(200, 200 ,200 ,255), sf::Color(150 ,150 ,150, 255));
        this->playButton->GetTransform()->SetScale(scaleFactor);
        this->playButton->GetTransform()->SetPosition(sf::Vector2f(this->window->getSize().x / 2, 270*scaleFactor.y));
        this->entities.push_back(std::unique_ptr<Engine::Entity>(this->playButton));

        // Create Settings Button
        this->settingsButton = new Engine::Entities::TextButton("Settings", [this]() { this->OnSettingsButtonClick(); }, "GameFont", 40);
        this->settingsButton->SetActionOnRelease(false);
        this->settingsButton->SetBackgroundTexture(Engine::ResourceManager::ResourceManager::GetTextureManager()->GetTexture("tile64_light"));
        this->settingsButton->SetBackgroundColors(sf::Color::White, sf::Color(200, 200 ,200 ,255), sf::Color(150 ,150 ,150, 255));
        this->settingsButton->GetTransform()->SetScale(scaleFactor);
        this->settingsButton->GetTransform()->SetPosition(sf::Vector2f(this->window->getSize().x / 2, 360*scaleFactor.y));
        this->entities.push_back(std::unique_ptr<Engine::Entity>(this->settingsButton));
    }

    void MenuScene::UpdateBehavior(float deltaTime) {
        this->playButton->Update(deltaTime);
        this->settingsButton->Update(deltaTime);
    }

    void MenuScene::HandleEvent(const std::optional<sf::Event>& event) {
    }

    void MenuScene::RenderBehavior() {
        // Render the menu scene
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
