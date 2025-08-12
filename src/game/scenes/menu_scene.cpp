#include "menu_scene.hpp"

namespace GameScene {

    void MenuScene::Start() {
        // Initialize the menu scene
        rectangle.setSize(sf::Vector2f(200, 100));
        rectangle.setFillColor(sf::Color::Green);
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
