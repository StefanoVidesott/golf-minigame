#pragma once

#include "components.hpp"

namespace Engine {
    namespace Components {
        class TextComponent : public Component {
            public:
                TextComponent(const sf::Font&, const std::string&, unsigned int = 30);
                TextComponent(const std::string, const std::string&, unsigned int = 30);
                ~TextComponent() override = default;

                void SetText(const std::string&);
                void SetFont(const sf::Font&);
                void SetCharacterSize(unsigned int);
                void SetStyle(sf::Text::Style);
                void SetFillColor(const sf::Color&);
                void SetOutlineColor(const sf::Color&);
                void SetOutlineThickness(float);
                void SetOrigin(const sf::Vector2f&);

                [[nodiscard]] const sf::String& GetString() const;
                [[nodiscard]] const sf::Font* GetFont() const;
                [[nodiscard]] unsigned int GetCharacterSize() const;
                [[nodiscard]] uint32_t GetStyle() const;
                [[nodiscard]] sf::Color GetFillColor() const;
                [[nodiscard]] sf::Color GetOutlineColor() const;
                [[nodiscard]] float GetOutlineThickness() const;

                // ---- Component Methods ----
                void Update(float) override;
                void Render(sf::RenderWindow*) override;

                void SetPosition(const sf::Vector2f&) override;
                void SetRotation(sf::Angle) override;
                void SetScale(const sf::Vector2f&) override;

                [[nodiscard]] sf::FloatRect GetGlobalBounds() const override;
                [[nodiscard]] sf::Vector2f GetOrigin() const override;
                [[nodiscard]] sf::Vector2f GetPosition() const override;
                [[nodiscard]] sf::Angle GetRotation() const override;
                [[nodiscard]] sf::Vector2f GetScale() const override;
            private:
                sf::Text text;
        };
    } // namespace Components
} // namespace Engine
