#include "transform_component.hpp"
#include "../entity.hpp"

namespace Engine {
    namespace Components {
        TransformComponent::TransformComponent()
            : position(0.f, 0.f), rotation(0.f), scale(1.f, 1.f) {}

        TransformComponent::TransformComponent(const sf::Vector2f& pos)
            : position(pos), rotation(0.f), scale(1.f, 1.f) {
                this->UpdateEntityTransform();
            }

        void TransformComponent::SetPosition(const sf::Vector2f& pos) {
            position = pos;
            this->UpdateEntityPosition();
        }

        void TransformComponent::Move(const sf::Vector2f& delta) {
            position += delta;
            this->UpdateEntityPosition();
        }

        void TransformComponent::SetRotation(float rot) {
            rotation = rot;
            this->UpdateEntityRotation();
        }

        void TransformComponent::Rotate(float delta) {
            rotation += delta;
            this->UpdateEntityRotation();
        }

        void TransformComponent::SetScale(const sf::Vector2f& s) {
            scale = s;
            this->UpdateEntityScale();
        }

        [[nodiscard]] sf::Vector2f TransformComponent::GetPosition() const {
            return position;
        }

        [[nodiscard]] float TransformComponent::GetRotation() const {
            return rotation;
        }

        sf::Vector2f TransformComponent::GetScale() const {
            return scale;
        }

        void TransformComponent::Update(float deltaTime) {
            // Update logic can be added here if needed
        }

        void TransformComponent::Render(sf::RenderWindow* window) {
        }

        void TransformComponent::UpdateEntityTransform() {
            if (this->owner) {
                for (Components::Component* component : this->owner->GetComponentList()) {
                    if (component) {
                        component->SetPosition(this->GetPosition());
                        component->SetRotation(this->GetRotation());
                        component->SetScale(this->GetScale());
                    }
                }
            }
        }

        void TransformComponent::UpdateEntityPosition() {
            if (this->owner) {
                for (Components::Component* component : this->owner->GetComponentList()) {
                    if (component) {
                        component->SetPosition(this->GetPosition());
                    }
                }
            }
        }


        void TransformComponent::UpdateEntityRotation() {
            if (this->owner) {
                for (Components::Component* component : this->owner->GetComponentList()) {
                    if (component) {
                        component->SetRotation(this->GetRotation());
                    }
                }
            }
        }


        void TransformComponent::UpdateEntityScale() {
            if (this->owner) {
                for (Components::Component* component : this->owner->GetComponentList()) {
                    if (component) {
                        component->SetScale(this->GetScale());
                    }
                }
            }
        }

    } // namespace Components
} // namespace Engine