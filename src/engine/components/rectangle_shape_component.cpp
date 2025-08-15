#include "rectangle_shape_component.hpp"

namespace Engine {
    namespace Components {

        RectangleShapeComponent::RectangleShapeComponent() {
            this->shape.setSize(sf::Vector2f(100.0f, 100.0f));
            this->shape.setFillColor(sf::Color::Green);
        }

        RectangleShapeComponent::RectangleShapeComponent(sf::Vector2f size) {
            this->shape.setSize(size);
            this->shape.setFillColor(sf::Color::Green);
        }

        void RectangleShapeComponent::SetSize(const sf::Vector2f& size) {
            this->shape.setSize(size);
        }

        void RectangleShapeComponent::SetFillColor(const sf::Color& color) {
            this->shape.setFillColor(color);
        }

        [[nodiscard]] sf::Vector2f RectangleShapeComponent::GetSize() const {
            return this->shape.getSize();
        }

        [[nodiscard]] sf::Color RectangleShapeComponent::GetFillColor() const {
            return this->shape.getFillColor();
        }

        void RectangleShapeComponent::Update(float deltaTime) {
            // Update logic for the rectangle shape
        }

        void RectangleShapeComponent::Render(sf::RenderWindow* window) {
            window->draw(this->shape);
        }

    } // namespace Components
} // namespace Engine
