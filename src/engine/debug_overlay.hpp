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

                std::string GetName() const override;

            private:
                void Initialize();

                Entity *overlayText = nullptr;
                Components::TextComponent *textComponent = nullptr;
                unsigned int textSize = 15;

                InputManager *inputManager;

                Scene **currentScene;
                std::stack<Scene*> *engine_scenes;
                std::vector<Scene*> *engine_overlays;

                float fps = 0.0f;
                float frameTime = 0.0f;
                int entityCount = 0;
            };
    } // namespace OverlayScene
} // namespace Engine
