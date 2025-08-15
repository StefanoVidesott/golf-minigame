#pragma once

#include "components.hpp"

namespace Engine {
    namespace Components {
        class RectangleShapeComponent : public Component {
            public:
                RectangleShapeComponent();
                RectangleShapeComponent(sf::Vector2f);
                ~RectangleShapeComponent() override = default;

                void SetSize(const sf::Vector2f&);
                void SetFillColor(const sf::Color&);
                void SetOutlineColor(const sf::Color&);
                void SetOutlineThickness(float);

                [[nodiscard]] sf::Vector2f GetSize() const;
                [[nodiscard]] sf::Color GetFillColor() const;
                [[nodiscard]] sf::Color GetOutlineColor() const;
                [[nodiscard]] float GetOutlineThickness() const;

                void Update(float) override;
                void Render(sf::RenderWindow*) override;
            private:
                sf::RectangleShape shape;
        };
    } // namespace Components
} // namespace Engine
