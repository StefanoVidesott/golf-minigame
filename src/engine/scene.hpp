#pragma once

#include "entity.hpp"

#include "entities/text_button.hpp"

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

                virtual std::string GetName() const = 0;

                sf::RenderWindow* window = nullptr;
                bool active = false;
                bool visible = true;

                std::vector<std::unique_ptr<Entity>> entities;
        };

    } // namespace Scene
} // namespace Engine
