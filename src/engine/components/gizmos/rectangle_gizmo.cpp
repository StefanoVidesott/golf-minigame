#include "rectangle_gizmo.hpp"

namespace Engine {
    namespace Gizmo {

        RectangleGizmo::RectangleGizmo() : shape() {
            this->shape.setFillColor(sf::Color(0,0,0,0));
            this->shape.setOutlineColor(sf::Color::Red);
            this->shape.setOutlineThickness(1.f);
        }

        void RectangleGizmo::Render(sf::RenderWindow* window) {
            if (this->isVisible) {
                window->draw(this->shape);
            }
        }

        void RectangleGizmo::SetPosition(const sf::Vector2f& position) {
            this->shape.setPosition(position);
        }

        void RectangleGizmo::SetRotation(sf::Angle angle) {
            this->shape.setRotation(angle);
        }

        void RectangleGizmo::SetOrigin(const sf::Vector2f& origin) {
            this->shape.setOrigin(origin);
        }

        void RectangleGizmo::SetSize(const sf::Vector2f& size) {
            this->shape.setSize(size);
        }

        void RectangleGizmo::SetColor(const sf::Color& color) {
            this->shape.setOutlineColor(color);
        }
    }
}