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

        void RectangleShapeComponent::SetOutlineColor(const sf::Color& color) {
            this->shape.setOutlineColor(color);
        }

        void RectangleShapeComponent::SetOutlineThickness(float thickness) {
            this->shape.setOutlineThickness(thickness);
        }

        void RectangleShapeComponent::SetTexture(const std::string& textureId) {
            this->shape.setTexture(&ResourceManager::ResourceManager::GetTextureManager()->GetTexture(textureId));
        }

        void RectangleShapeComponent::SetTexture(const sf::Texture& texture) {
            this->shape.setTexture(&texture);
        }

        [[nodiscard]] sf::Vector2f RectangleShapeComponent::GetSize() const {
            return this->shape.getSize();
        }

        [[nodiscard]] sf::Color RectangleShapeComponent::GetFillColor() const {
            return this->shape.getFillColor();
        }

        [[nodiscard]] sf::Color RectangleShapeComponent::GetOutlineColor() const {
            return this->shape.getOutlineColor();
        }

        [[nodiscard]] float RectangleShapeComponent::GetOutlineThickness() const {
            return this->shape.getOutlineThickness();
        }

        [[nodiscard]] sf::FloatRect RectangleShapeComponent::GetGlobalBounds() const {
            return this->shape.getGlobalBounds();
        }

        void RectangleShapeComponent::Update(float deltaTime) {
            // Update logic for the rectangle shape
        }

        void RectangleShapeComponent::Render(sf::RenderWindow* window) {
            window->draw(this->shape);
        }

        void RectangleShapeComponent::SetPosition(const sf::Vector2f& position) {
            this->shape.setPosition(position);
        }

        void RectangleShapeComponent::SetRotation(sf::Angle angle) {
            this->shape.setRotation(angle);
        }

        void RectangleShapeComponent::SetScale(const sf::Vector2f& scale) {
            this->shape.setScale(scale);
        }

        void RectangleShapeComponent::SetOrigin(const sf::Vector2f& origin) {
            this->shape.setOrigin(origin);
        }

    } // namespace Components
} // namespace Engine
