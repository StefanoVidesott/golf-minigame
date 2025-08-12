#include "menu_scene.hpp"

namespace GameScene {

    void MenuScene::Start() {
        // Initialize the menu scene
        this->rectangle.setSize(sf::Vector2f(200, 100));
        this->rectangle.setFillColor(sf::Color::Green);

        Engine::ResourceManager::ResourceManager::loadFont("TitleFont", "res/font/font.ttf");
        this->titleFont = &Engine::ResourceManager::ResourceManager::getFont("TitleFont");

        this->titleText = new sf::Text(*this->titleFont, "Golf Minigame");
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
            window->draw(*titleText);
        }
    }

} // namespace Scene
