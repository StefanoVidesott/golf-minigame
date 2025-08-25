#pragma once

#include "../entity.hpp"

namespace Engine {
    namespace Entities {
        class TextButton : public Entity {
            public:
                TextButton(const std::string&, std::function<void()>, const std::string& = "default", int = 30); //
                ~TextButton() = default;

                void SetTextString(const std::string&);
                void SetTextFont(const std::string&);
                void SetTextFont(const sf::Font&);
                void SetTextSize(unsigned int);
                void SetTextColor(const sf::Color&);
                void SetTextOutlineColor(const sf::Color&);
                void SetTextOutlineThickness(float);

                void SetBackgroundColors(const sf::Color&, const sf::Color&, const sf::Color&);
                void SetBackgroundMargin(const sf::Vector2f&);
                void SetBackgroundOutlineColor(const sf::Color&);
                void SetBackgroundOutlineThickness(float);
                void SetBackgroundTexture(const sf::Texture&);

                void SetOnClick(std::function<void()>);
                void SetActionOnRelease(bool);

                void Update(float); //

                [[nodiscard]] sf::FloatRect GetGlobalBounds(); //
            private:
                void UpdateBackground(); //
                sf::Vector2f backgroundMargin = sf::Vector2f(20.f, 15.f);

                sf::Color normalBackgroundColor = sf::Color::Blue;
                sf::Color hoverBackgroundColor = sf::Color::Cyan;
                sf::Color clickedBackgroundColor = sf::Color::Green;

                InputManager *inputManager;

                std::function<void()> onClick;
                bool wasButtonPressed = false;
                bool wasButtonReleased = true;

                bool actionOnRelease = true;
        };
    } // namespace Entities
} // namespace Engine