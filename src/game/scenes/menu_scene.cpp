#include "menu_scene.hpp"

namespace GameScene {

    void MenuScene::Start() {
        // Initialize the menu scene
        this->rectangle.setSize(sf::Vector2f(200, 100));
        this->rectangle.setFillColor(sf::Color::Green);

        Engine::ResourceManager::ResourceManager::loadFont("TitleFont", "res/font/font.ttf");

        Engine::Entity *titleEntity = new Engine::Entity();
        Engine::Components::TextComponent *titleTextComponent = new Engine::Components::TextComponent("TitleFont", "Golf Minigame", 50);
        titleEntity->AddComponent(titleTextComponent);
        this->entities.push_back(titleEntity);

    }

    void MenuScene::FixedUpdate(float fixedDeltaTime) {
        // Update the menu scene at a fixed interval
    }

    void MenuScene::Update(float deltaTime) {
        // Update the menu scene
    }

    void MenuScene::HandleEvent(const std::optional<sf::Event>& event) {
        // Handle events for the menu scene
    }

    void MenuScene::Render() {
        // Render the menu scene
        if (window) {
            window->draw(rectangle);
        }
    }

} // namespace Scene
