#include "sprite_component.hpp"

namespace Engine {
    namespace Components {

        SpriteComponent::SpriteComponent(sf::Texture& texture) : sprite(texture) {
        }

        void SpriteComponent::Update(float deltaTime) {
            // Update logic for the sprite component
        }

        void SpriteComponent::Render(sf::RenderWindow* window) {
            if (window) {
                window->draw(this->sprite);
            }
        }

        void SpriteComponent::SetPosition(const sf::Vector2f& position) {
            this->sprite.setPosition(position);
        }

        void SpriteComponent::SetScale(const sf::Vector2f& scale) {
            this->sprite.setScale(scale);
        }

    } // namespace Components
} // namespace Engine