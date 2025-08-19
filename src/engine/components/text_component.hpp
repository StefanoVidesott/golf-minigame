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

                [[nodiscard]] const sf::String& getString() const;
                [[nodiscard]] const sf::Font* GetFont() const;
                [[nodiscard]] unsigned int GetCharacterSize() const;
                [[nodiscard]] uint32_t GetStyle() const;
                [[nodiscard]] sf::FloatRect GetGlobalBounds() const;

                void Update(float) override;
                void Render(sf::RenderWindow*) override;
                void SetPosition(const sf::Vector2f& position) override;
            private:
                sf::Text text;
        };
    } // namespace Components
} // namespace Engine
