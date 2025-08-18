#pragma once

#include "../input_manager.hpp"

namespace Engine {

    class Entity;

    namespace Components {

        class Component {
            public:
                Component() = default;
                virtual ~Component() = default;

                virtual void Update(float) = 0;
                virtual void Render(sf::RenderWindow*) = 0;

                virtual void SetPosition(const sf::Vector2f&) {}
                virtual void SetRotation(float) {}
                virtual void SetScale(const sf::Vector2f&) {}

                void SetOwner(Engine::Entity* _owner) {
                    this->owner = _owner;
                }
            protected:
                Engine::Entity *owner;
        };

    } // namespace Components
} // namespace Engine
