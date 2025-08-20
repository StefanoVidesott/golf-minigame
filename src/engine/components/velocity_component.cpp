#include "velocity_component.hpp"
#include "../entity.hpp"

namespace Engine {
    namespace Components {

        VelocityComponent::VelocityComponent() {
        }

        void VelocityComponent::Update(float deltaTime) {
            if (this->velocity != sf::Vector2f(0, 0)) {
                float factor = 1.f - this->friction * deltaTime;
                if (factor < 0.f) {
                    factor = 0.f;
                }
                this->owner->GetTransform()->Move(this->velocity * deltaTime);
                this->velocity *= (factor);
            }
            if (this->velocity.x < this->threshold && this->velocity.x > -this->threshold) {
                this->velocity.x = 0;
            }
            if (this->velocity.y < this->threshold && this->velocity.y > -this->threshold) {
                this->velocity.y = 0;
            }
        }

        void VelocityComponent::Render(sf::RenderWindow* window) {
            // No rendering needed for velocity component
        }

        void VelocityComponent::SetPosition(const sf::Vector2f& position) {
            // No position setting needed for velocity component
        }

        void VelocityComponent::SetVelocity(const sf::Vector2f& velocity) {
            this->velocity = velocity;
        }

        void VelocityComponent::SetFriction(float friction) {
            this->friction = friction;
        }

        void VelocityComponent::SetThreshold(float threshold) {
            this->threshold = threshold;
        }

        [[nodiscard]] const sf::Vector2f& VelocityComponent::GetVelocity() const {
            return this->velocity;
        }

        [[nodiscard]] float VelocityComponent::GetFriction() const {
            return this->friction;
        }

        [[nodiscard]] float VelocityComponent::GetThreshold() const {
            return this->threshold;
        }

    } // namespace Components
} // namespace Engine
