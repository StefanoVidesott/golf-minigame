#pragma once

#include <SFML/Graphics.hpp>

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

                sf::RenderWindow* window = nullptr; // Pointer to the window for rendering
                bool continueInPause = false; // Flag to check if the scene should continue in pause
                bool loaded = false; // Flag to check if the scene is loaded
                bool active = false; // Flag to check if the scene is active
        };

    } // namespace Scene
} // namespace Engine