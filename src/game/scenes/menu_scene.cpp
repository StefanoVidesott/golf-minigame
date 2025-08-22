#include "menu_scene.hpp"

namespace ApplicationScene {

    void MenuScene::Start() {
        this->inputManager = Engine::ResourceManager::ResourceManager::GetInputManager();
        Engine::ResourceManager::ResourceManager::LoadFont("TitleFont", "res/font/font.ttf");
        Engine::ResourceManager::ResourceManager::LoadTexture("background", "res/gfx/bg.png");

        Engine::Entity *bg = new Engine::Entity();
        Engine::Components::SpriteComponent *bgSpriteComponent = new Engine::Components::SpriteComponent(Engine::ResourceManager::ResourceManager::GetTexture("background"));
        bg->GetTransform()->SetScale(sf::Vector2f(1.5f, 1.5f));
        bg->AddComponent("BackgroundSprite", std::unique_ptr<Engine::Components::Component>(bgSpriteComponent));
        this->entities.push_back(std::unique_ptr<Engine::Entity>(bg));

        std::unique_ptr<Engine::Entity> titleEntity = std::make_unique<Engine::Entity>();
        Engine::Components::TextComponent *titleTextComponent = new Engine::Components::TextComponent("TitleFont", "Gooolf!", 115);
        titleTextComponent->SetOrigin(sf::Vector2f(titleTextComponent->GetGlobalBounds().size.x/2, titleTextComponent->GetGlobalBounds().size.y/2));
        titleTextComponent->SetOutlineColor(sf::Color::Black);
        titleTextComponent->SetOutlineThickness(5.f);
        titleEntity->GetTransform()->SetPosition(sf::Vector2f(this->window->getSize().x/2, 125));

        titleEntity->AddComponent("TitleText", std::unique_ptr<Engine::Components::Component>(titleTextComponent));
        this->entities.push_back(std::move(titleEntity));
    }

    void MenuScene::UpdateBehavior(float deltaTime) {
    }

    void MenuScene::HandleEvent(const std::optional<sf::Event>& event) {
    }

    void MenuScene::RenderBehavior() {
        // Render the menu scene
    }

    std::string MenuScene::GetName() const {
        return "MenuScene";
    }

} // namespace Scene
