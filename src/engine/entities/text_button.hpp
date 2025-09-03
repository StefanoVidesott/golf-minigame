// text_button.hpp
#pragma once

#include "../entity.hpp"

namespace Engine {
    namespace Entities {

        class TextButton : public Entity {
        public:
            TextButton(const std::string& text,
                    std::function<void()> onClick,
                    const std::string& fontName = "default",
                    int fontSize = 30);
            ~TextButton() = default;

            // text
            void SetTextString(const std::string& text);
            void SetTextFont(const std::string& fontName);
            void SetTextFont(const sf::Font& font);
            void SetTextSize(unsigned int size);
            void SetTextColor(const sf::Color& color);
            void SetTextOutlineColor(const sf::Color& color);
            void SetTextOutlineThickness(float thickness);

            // background
            void SetBackgroundColors(const sf::Color& normal,
                                    const sf::Color& hover,
                                    const sf::Color& clicked);
            void SetBackgroundMargin(const sf::Vector2f& margin);
            void SetBackgroundOutlineColor(const sf::Color& color);
            void SetBackgroundOutlineThickness(float thickness);
            void SetBackgroundTexture(const sf::Texture& texture);

            // behavior
            void SetOnClick(std::function<void()> callback);
            void SetActionOnRelease(bool action);
            void EnableAutoBackgroundResize(bool enabled);

            void Update(float deltaTime);

            [[nodiscard]] sf::FloatRect GetGlobalBounds();
            [[nodiscard]] sf::FloatRect GetLocalBounds();

        private:
            void UpdateBackground();

            // settings
            sf::Vector2f backgroundMargin {20.f, 15.f};
            sf::Color normalBackgroundColor {sf::Color::Blue};
            sf::Color hoverBackgroundColor {sf::Color::Cyan};
            sf::Color clickedBackgroundColor {sf::Color::Green};
            bool actionOnRelease {true};
            bool autoCorrectBg {true};

            // state
            InputManager* inputManager {nullptr};
            std::function<void()> onClick;
            bool wasButtonPressed {false};
            bool wasButtonReleased {true};
        };

    } // namespace Entities
} // namespace Engine
