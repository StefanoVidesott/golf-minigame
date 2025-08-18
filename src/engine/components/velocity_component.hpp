#pragma once

#include "transform_component.hpp"

namespace Engine {
    namespace Components {
        class VelocityComponent : public Component {
            public:
                VelocityComponent();
                ~VelocityComponent() override = default;

                void SetVelocity(const sf::Vector2f&);
                void SetFriction(float);
                void SetThreshold(float);

                [[nodiscard]] const sf::Vector2f& GetVelocity() const;
                [[nodiscard]] float GetFriction() const;
                [[nodiscard]] float GetThreshold() const;

                void Update(float) override;
                void Render(sf::RenderWindow*) override;
                void SetPosition(const sf::Vector2f& position) override;
            private:
                sf::Vector2f velocity = sf::Vector2f(0, 0);
                float friction = 1.0f;
                float threshold = 0.15f;
        };
    } // namespace Components
} // namespace Engine
