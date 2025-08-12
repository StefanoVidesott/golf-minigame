#pragma once

#include "resource_manager.hpp"

namespace Engine {
    namespace Scene {

        class Scene {
            public:
                Scene() = default;
                virtual ~Scene() = default;

                virtual void Start() = 0;
                virtual void FixedUpdate(float fixedDeltaTime) = 0;
                virtual void Update(float deltaTime) = 0;
                virtual void HandleEvent(const std::optional<sf::Event>& event) = 0;
                virtual void Render() = 0;

                sf::RenderWindow* window = nullptr;
                bool continueInPause = false;
                bool loaded = false;
                bool active = false;
        };

    } // namespace Scene
} // namespace Engine