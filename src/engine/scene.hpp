#pragma once

#include "entity.hpp"

namespace Engine {
    namespace Scene {

        class Scene {
            public:
                Scene() = default;
                virtual ~Scene() = default;

                virtual void Start() = 0;
                virtual void FixedUpdate(float) = 0;
                virtual void Update(float) = 0;
                virtual void HandleEvent(const std::optional<sf::Event>&) = 0;
                virtual void Render() = 0;

                sf::RenderWindow* window = nullptr;
                bool continueInPause = false;
                bool loaded = false;
                bool active = false;
                std::vector<Entity*> entities;
        };

    } // namespace Scene
} // namespace Engine