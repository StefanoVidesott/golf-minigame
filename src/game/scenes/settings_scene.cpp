#include "settings_scene.hpp"

namespace ApplicationScene {

    void SettingsScene::Start() {
        // Create Background Entity
        Engine::Entity *bg = new Engine::Entity();
        Engine::Components::SpriteComponent *bgSpriteComponent = new Engine::Components::SpriteComponent(Engine::ResourceManager::ResourceManager::GetTextureManager()->GetTexture("background"));
        bg->AddComponent("BackgroundSprite", std::unique_ptr<Engine::Components::Component>(bgSpriteComponent));
        sf::Vector2u bgSize = Engine::ResourceManager::ResourceManager::GetTextureManager()->GetTexture("background").getSize();
        sf::Vector2u windowSize = this->window->getSize();
        sf::Vector2f scaleFactor = sf::Vector2f(static_cast<float>(windowSize.x) / bgSize.x, static_cast<float>(windowSize.y) / bgSize.y);
        bg->GetTransform()->SetScale(scaleFactor);
        this->entities.push_back(std::unique_ptr<Engine::Entity>(bg));

    }

    void SettingsScene::UpdateBehavior(float deltaTime) {
        // Update the game scene
    }

    void SettingsScene::HandleEvent(const std::optional<sf::Event>& event) {
        // Handle events for the game scene
    }

    void SettingsScene::RenderBehavior() {
        // Render the game scene
    }

    std::string SettingsScene::GetName() const {
        return "SettingsScene";
    }

} // namespace ApplicationScene
