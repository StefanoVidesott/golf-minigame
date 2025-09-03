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
            bool isContained = this->GetGlobalBounds().contains(static_cast<sf::Vector2f>(this->inputManager->GetMousePosition()));
            Engine::Components::RectangleShapeComponent* backgroundComponent = this->GetComponent<Engine::Components::RectangleShapeComponent>("background");
            if (isContained) {
                if (this->inputManager->IsMouseButtonDown(sf::Mouse::Button::Left)) {
                    backgroundComponent->SetFillColor(this->clickedBackgroundColor);
                    if (!this->actionOnRelease && this->wasButtonReleased) {
                        this->onClick();
                    }
                    this->wasButtonPressed = true;
                    this->wasButtonReleased = false;
                } else {
                    backgroundComponent->SetFillColor(this->hoverBackgroundColor);
                }
            } else {
                backgroundComponent->SetFillColor(this->normalBackgroundColor);
            }

            if (!this->inputManager->IsMouseButtonDown(sf::Mouse::Button::Left)) {
                if (this->wasButtonPressed) {
                    this->wasButtonReleased = true;
                    this->wasButtonPressed = false;
                    if(this->actionOnRelease && isContained) {
                        this->onClick();
                    }
                }
            }
        }

        [[nodiscard]] sf::FloatRect TextButton::GetGlobalBounds() {
            return this->GetComponent<Engine::Components::RectangleShapeComponent>("background")->GetGlobalBounds();
        }

        [[nodiscard]] sf::FloatRect TextButton::GetLocalBounds() {
            return this->GetComponent<Engine::Components::RectangleShapeComponent>("background")->GetLocalBounds();
        }

        void TextButton::SetTextString(const std::string& text) {
            this->GetComponent<Engine::Components::TextComponent>("text")->SetString(text);
            if (this->autoCorrectBg) {
                this->UpdateBackground();
            }
        }

        void TextButton::SetTextFont(const std::string& fontName) {
            this->GetComponent<Engine::Components::TextComponent>("text")->SetFont(fontName);
            this->UpdateBackground();
        }

        void TextButton::SetTextFont(const sf::Font& font) {
            this->GetComponent<Engine::Components::TextComponent>("text")->SetFont(font);
            this->UpdateBackground();
        }

        void TextButton::SetTextSize(unsigned int size) {
            this->GetComponent<Engine::Components::TextComponent>("text")->SetCharacterSize(size);
            this->UpdateBackground();
        }

        void TextButton::SetTextColor(const sf::Color& color) {
            this->GetComponent<Engine::Components::TextComponent>("text")->SetFillColor(color);
        }

        void TextButton::SetTextOutlineColor(const sf::Color& color) {
            this->GetComponent<Engine::Components::TextComponent>("text")->SetOutlineColor(color);
            this->UpdateBackground();
        }

        void TextButton::SetTextOutlineThickness(float thickness) {
            this->GetComponent<Engine::Components::TextComponent>("text")->SetOutlineThickness(thickness);
            this->UpdateBackground();
        }

        void TextButton::SetBackgroundColors(const sf::Color& normal, const sf::Color& hover, const sf::Color& clicked) {
            this->normalBackgroundColor = normal;
            this->hoverBackgroundColor = hover;
            this->clickedBackgroundColor = clicked;
            this->GetComponent<Engine::Components::RectangleShapeComponent>("background")->SetFillColor(normal);
        }

        void TextButton::SetBackgroundMargin(const sf::Vector2f& margin) {
            this->backgroundMargin = margin;
            this->UpdateBackground();
        }

        void TextButton::SetBackgroundOutlineColor(const sf::Color& color) {
            this->GetComponent<Engine::Components::RectangleShapeComponent>("background")->SetOutlineColor(color);
        }

        void TextButton::SetBackgroundOutlineThickness(float thickness) {
            this->GetComponent<Engine::Components::RectangleShapeComponent>("background")->SetOutlineThickness(thickness);
        }

        void TextButton::SetBackgroundTexture(const sf::Texture& texture) {
            this->GetComponent<Engine::Components::RectangleShapeComponent>("background")->SetTexture(texture);
        }

        void TextButton::SetActionOnRelease(bool action) {
            this->actionOnRelease = action;
        }

        void TextButton::EnableAutoBackgroundResize(bool enabled) {
            this->autoCorrectBg = enabled;
        }

    }
}