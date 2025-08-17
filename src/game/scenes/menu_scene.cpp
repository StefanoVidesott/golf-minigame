#include "menu_scene.hpp"

namespace ApplicationScene {

    void MenuScene::Start() {
        this->inputManager = Engine::ResourceManager::ResourceManager::GetInputManager();
        Engine::ResourceManager::ResourceManager::loadFont("TitleFont", "res/font/font.ttf");

        titleEntity = new Engine::Entity();
        Engine::Components::TextComponent *titleTextComponent = new Engine::Components::TextComponent("TitleFont", "Golf Minigame", 50);
        titleEntity->AddComponent("TitleText", std::unique_ptr<Engine::Components::Component>(titleTextComponent));
        this->entities.push_back(std::unique_ptr<Engine::Entity>(titleEntity));
    }

    void MenuScene::UpdateBehavior(float deltaTime) {
        sf::Vector2f direction;
        if (this->inputManager->IsKeyDown(sf::Keyboard::Key::Left)) {
            direction.x -= 1;
        }
        if (this->inputManager->IsKeyDown(sf::Keyboard::Key::Right)) {
            direction.x += 1;
        }
        if (this->inputManager->IsKeyDown(sf::Keyboard::Key::Up)) {
            direction.y -= 1;
        }
        if (this->inputManager->IsKeyDown(sf::Keyboard::Key::Down)) {
            direction.y += 1;
        }
        this->titleEntity->GetTransform()->Move(direction*200.0f*deltaTime);
        // this->titleEntity->GetTransform()->SetPosition(sf::Vector2f(this->inputManager->GetMousePosition().x, this->inputManager->GetMousePosition().y));
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
