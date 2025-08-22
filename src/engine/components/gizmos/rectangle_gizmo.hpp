#pragma once

#include "./gizmo.hpp"

namespace Engine {
    namespace Gizmo {

        class RectangleGizmo : public Gizmo {
            public:
                RectangleGizmo();
                ~RectangleGizmo() = default;

                void Render(sf::RenderWindow*) override;
                void SetPosition(const sf::Vector2f&) override;
                void SetRotation(sf::Angle) override;
                void SetOrigin(const sf::Vector2f&) override;
                void SetColor(const sf::Color&) override;

                void SetSize(const sf::Vector2f&);
            private:
                sf::RectangleShape shape;
        };

    }
}