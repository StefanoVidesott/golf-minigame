// src/engine/components/transform_component.hpp
#pragma once

#include "components.hpp"

namespace Engine {

    class Entity;

    namespace Components {
        class TransformComponent : public Component {
        public:
            TransformComponent();
            TransformComponent(const sf::Vector2f&);

            void SetPosition(const sf::Vector2f&);
            void Move(const sf::Vector2f&);

            void SetRotation(float);
            void Rotate(float);

            void SetScale(const sf::Vector2f&);

            [[nodiscard]] sf::Vector2f GetPosition() const;
            [[nodiscard]] float GetRotation() const;
            [[nodiscard]] sf::Vector2f GetScale() const;

            void Update(float) override;
            void Render(sf::RenderWindow*) override;

            Entity* owner = nullptr;
        private:
            void UpdateEntityComponents();

            sf::Vector2f position;
            float rotation;
            sf::Vector2f scale;
        };
    }
}
