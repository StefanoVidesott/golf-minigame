#pragma once

#include "entity.hpp"

namespace Engine {
    namespace Scene {

        class Scene {
            public:
                Scene() = default;
                virtual ~Scene();

                void Update(float);
                void Render();

                virtual void Start() = 0;
                virtual void UpdateBehavior(float) = 0;
                virtual void HandleEvent(const std::optional<sf::Event>&) = 0;
                virtual void RenderBehavior() = 0;

                sf::RenderWindow* window = nullptr;
                bool continueInPause = false;
                bool loaded = false;
                bool active = false;
                std::vector<std::unique_ptr<Entity>> entities;
        };

    } // namespace Scene
} // namespace Engine
