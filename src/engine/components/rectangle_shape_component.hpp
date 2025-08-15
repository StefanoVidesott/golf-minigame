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
                [[nodiscard]] sf::Vector2f GetSize() const;
                [[nodiscard]] sf::Color GetFillColor() const;

                void Update(float) override;
                void Render(sf::RenderWindow*) override;
            private:
                sf::RectangleShape shape;
        };
    } // namespace Components
} // namespace Engine
