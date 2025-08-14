#pragma once

#include "../input_manager.hpp"

namespace Engine {
    namespace Components {

        class Component {
            public:
                Component() = default;
                virtual ~Component() = default;

                virtual void Update(float) = 0;
                virtual void Render(sf::RenderWindow*) = 0;
        };

    } // namespace Components
} // namespace Engine
