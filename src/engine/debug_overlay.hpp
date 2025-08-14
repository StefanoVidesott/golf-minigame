#pragma once

#include "scene.hpp"

namespace Engine {
    namespace OverlayScene {

        class DebugOverlayScene : public Scene::Scene {
            public:
                DebugOverlayScene() = default;
                ~DebugOverlayScene() override = default;

                void Start() override;
                void UpdateBehavior(float) override;
                void HandleEvent(const std::optional<sf::Event>&) override;
                void RenderBehavior() override;

                Scene **currentScene;
                std::stack<Scene*> *engine_scenes;
                std::vector<Scene*> *engine_overlays;

            private:
                Entity *overlayText = nullptr;

                float fps = 0.0f; // frames per second
                float frameTime = 0.0f; // time taken to render a frame
                float frameTimeAccumulator = 0.0f; // accumulator for frame time
                int entityCount = 0; // number of entities in the current scene

                // TODO: implement background box

        };
    } // namespace OverlayScene
} // namespace Engine
