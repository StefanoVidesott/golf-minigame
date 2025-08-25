#pragma once

#include "./gizmos/gizmo.hpp"

namespace Engine {

    class Entity;

    namespace Components {

        class Component {
            public:
                Component() = default;
                virtual ~Component() = default;

                virtual void Update(float) {};
                virtual void Render(sf::RenderWindow*) {};

                virtual void SetPosition(const sf::Vector2f&) {}
                virtual void SetRotation(sf::Angle) {}
                virtual void SetScale(const sf::Vector2f&) {}

                [[nodiscard]] virtual sf::FloatRect GetGlobalBounds() const { return sf::FloatRect(); }
                [[nodiscard]] virtual sf::FloatRect GetLocalBounds() const { return sf::FloatRect(); }
                [[nodiscard]] virtual sf::Vector2f GetOrigin() const { return sf::Vector2f(); }
                [[nodiscard]] virtual sf::Vector2f GetPosition() const { return sf::Vector2f(); }
                [[nodiscard]] virtual sf::Angle GetRotation() const { return sf::Angle(); }
                [[nodiscard]] virtual sf::Vector2f GetScale() const { return sf::Vector2f(1.f, 1.f); }

                void SetOwner(Entity* _owner) {
                    this->owner = _owner;
                }

                void SetGizmoEnabled(bool enabled) {
                    this->gizmoEnabled = enabled;
                }

            protected:
                Entity *owner;
                bool gizmoEnabled = false;
        };

    } // namespace Components
} // namespace Engine
