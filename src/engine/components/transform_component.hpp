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
                void SetRotation(sf::Angle);
                void SetScale(const sf::Vector2f&);

                void Rotate(sf::Angle);
                void Move(const sf::Vector2f&);

                [[nodiscard]] sf::Vector2f GetPosition() const;
                [[nodiscard]] sf::Angle GetRotation() const;
                [[nodiscard]] sf::Vector2f GetScale() const;

                void Update(float) override;
                void Render(sf::RenderWindow*) override;
                void UpdateEntityTransform();
            private:
                void UpdateEntityPosition();
                void UpdateEntityRotation();
                void UpdateEntityScale();

                sf::Vector2f position;
                sf::Angle rotation;
                sf::Vector2f scale;
        };
    }
}
