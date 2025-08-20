#pragma once

#include "components.hpp"

namespace Engine {
    namespace Components {
        class SpriteComponent : public Component {
            public:
                SpriteComponent(sf::Texture&);
                ~SpriteComponent() override = default;

                void Update(float) override;
                void Render(sf::RenderWindow*) override;
                void SetPosition(const sf::Vector2f&) override;
                void SetScale(const sf::Vector2f&) override;
            private:
                sf::Sprite sprite;
        };
    } // namespace Components
} // namespace Engine
