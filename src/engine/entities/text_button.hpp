#pragma once

#include "../entity.hpp"

namespace Engine {
    namespace Entities {
        class TextButton : public Entity {
            public:
                TextButton(const std::string&, const std::string& = "default", int = 30);
                ~TextButton() = default;

                void SetTextString(const std::string&);
                void SetTextFont(const sf::Font&);
                void SetTextSize(unsigned int);
                void SetTextColor(const sf::Color&);
                void SetTextOutlineColor(const sf::Color&);
                void SetTextOutlineThickness(float);

                void SetBackgroundColor(const sf::Color&);
                void SetBackgroundMargin(const sf::Vector2f&);
                void SetBackgroundOutlineColor(const sf::Color&);
                void SetBackgroundOutlineThickness(float);

                void Update(float);

                [[nodiscard]] sf::FloatRect GetGlobalBounds();
            private:
                void UpdateBackground();
                sf::Vector2f backgroundMargin = sf::Vector2f(20.f, 15.f);

                sf::Color normalBackgroundColor = sf::Color::Blue;
                sf::Color hoverBackgroundColor = sf::Color::Cyan;
                sf::Color clickedBackgroundColor = sf::Color::Green;

                InputManager *inputManager;
        };
    } // namespace Entities
} // namespace Engine