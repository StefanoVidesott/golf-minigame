#pragma once

#include "../../input_manager.hpp"

namespace Engine {
    namespace Gizmo {
        class Gizmo {
            public:
                Gizmo() = default;
                ~Gizmo() = default;

                // virtual void Update(float dt) = 0;
                virtual void Render(sf::RenderWindow* window) = 0;
                virtual void SetPosition(const sf::Vector2f& position) = 0;
                virtual void SetRotation(sf::Angle angle) = 0;
                virtual void SetOrigin(const sf::Vector2f& origin) = 0;
                virtual void SetVisible(bool visible) { this->isVisible = visible; };
                virtual void SetColor(const sf::Color& color) = 0;

            protected:
                bool isVisible = false;
        };
    }
}