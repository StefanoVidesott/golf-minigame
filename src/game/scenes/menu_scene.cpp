#include "menu_scene.hpp"

namespace ApplicationScene {

    void MenuScene::Start() {
        // Initialize the menu scene
        // this->rectangle.setSize(sf::Vector2f(200, 100));
        // this->rectangle.setFillColor(sf::Color::Green);

        // Engine::ResourceManager::ResourceManager::loadFont("TitleFont", "res/font/font.ttf");

        // Engine::Entity *titleEntity = new Engine::Entity();
        // Engine::Components::TextComponent *titleTextComponent = new Engine::Components::TextComponent("TitleFont", "Golf Minigame", 50);
        // titleEntity->AddComponent("TitleText", std::unique_ptr<Engine::Components::Component>(titleTextComponent));
        // this->entities.push_back(std::unique_ptr<Engine::Entity>(titleEntity));
    }

    void MenuScene::UpdateBehavior(float deltaTime) {
        // Update the menu scene
    }

    void MenuScene::HandleEvent(const std::optional<sf::Event>& event) {
        // Handle events for the menu scene
    }

    void MenuScene::RenderBehavior() {
        // Render the menu scene
    }

} // namespace Scene
