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

        this->titleEntity = new Engine::Entity();
        Engine::Components::TextComponent *titleTextComponent = new Engine::Components::TextComponent("TitleFont", "Golf Minigame", 50);
        Engine::Components::VelocityComponent *velocityComponent = new Engine::Components::VelocityComponent();
        velocityComponent->SetFriction(1.75f);
        this->titleEntity->AddComponent("TitleText", std::unique_ptr<Engine::Components::Component>(titleTextComponent));
        this->titleEntity->AddComponent("Velocity", std::unique_ptr<Engine::Components::Component>(velocityComponent));
        this->entities.push_back(std::unique_ptr<Engine::Entity>(this->titleEntity));
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
        if (direction != sf::Vector2f(0,0)) {
            direction = direction.normalized();
            sf::Vector2f velocityVector = direction * 250.0f;
            if (direction.x == 0) {
                velocityVector.x = this->titleEntity->GetComponent<Engine::Components::VelocityComponent>("Velocity")->GetVelocity().x;
            }
            else if (direction.y == 0) {
                velocityVector.y = this->titleEntity->GetComponent<Engine::Components::VelocityComponent>("Velocity")->GetVelocity().y;
            }
            this->titleEntity->GetComponent<Engine::Components::VelocityComponent>("Velocity")->SetVelocity(velocityVector);
        }
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
