#include "text_button.hpp"

namespace Engine {
    namespace Entities {
        TextButton::TextButton(const std::string& text, std::function<void()> onClick, const std::string& fontName, int fontSize) {
            this->inputManager = Engine::ResourceManager::ResourceManager::GetInputManager();

            this->onClick = onClick;

            Components::TextComponent* textComponent = new Components::TextComponent(fontName, text, fontSize);
            Components::RectangleShapeComponent* backgroundComponent = new Components::RectangleShapeComponent();

            this->AddComponent("text", std::make_unique<Components::TextComponent>(*textComponent));
            this->AddComponent("background", std::make_unique<Components::RectangleShapeComponent>(*backgroundComponent));
            this->UpdateBackground();
        }

        void TextButton::UpdateBackground() {
            Components::RectangleShapeComponent* backgroundComponent = this->GetComponent<Engine::Components::RectangleShapeComponent>("background");
            Components::TextComponent* textComponent = this->GetComponent<Engine::Components::TextComponent>("text");

            sf::FloatRect textBounds = textComponent->GetLocalBounds();

            sf::Vector2f backgroundSize(textBounds.size.x + this->backgroundMargin.x * 2.f, textBounds.size.y + this->backgroundMargin.y * 2.f);
            backgroundComponent->SetSize(backgroundSize);

            textComponent->SetOrigin({textBounds.position.x + textBounds.size.x / 2.f, textBounds.position.y + textBounds.size.y / 2.f});
            backgroundComponent->SetOrigin(backgroundSize / 2.f);
        }


        void TextButton::Update(float deltaTime) {
            if (this->GetGlobalBounds().contains(static_cast<sf::Vector2f>(this->inputManager->GetMousePosition()))) {
                Engine::Components::RectangleShapeComponent* backgroundComponent = this->GetComponent<Engine::Components::RectangleShapeComponent>("background");
                if (this->inputManager->IsMouseButtonDown(sf::Mouse::Button::Left)) {
                    backgroundComponent->SetFillColor(this->clickedBackgroundColor);
                    if (this->wasButtonReleased) {
                        this->onClick();
                    }
                    this->wasButtonPressed = true;
                    this->wasButtonReleased = false;
                } else {
                    backgroundComponent->SetFillColor(this->hoverBackgroundColor);
                    if (this->wasButtonPressed) {
                        this->wasButtonReleased = true;
                        this->wasButtonPressed = false;
                    }
                }
            } else {
                this->GetComponent<Engine::Components::RectangleShapeComponent>("background")->SetFillColor(this->normalBackgroundColor);
            }
        }

        [[nodiscard]] sf::FloatRect TextButton::GetGlobalBounds() {
            return this->GetComponent<Engine::Components::RectangleShapeComponent>("background")->GetGlobalBounds();
        }

        void TextButton::SetTextString(const std::string& text) {
            this->GetComponent<Engine::Components::TextComponent>("text")->SetString(text);
            this->UpdateBackground();
        }

    }
}