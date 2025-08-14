#include "debug_overlay.hpp"

namespace Engine {
    namespace OverlayScene {

        void DebugOverlayScene::Start() {
            this->overlayText = new Entity();
            Components::TextComponent *titleTextComponent = new Components::TextComponent("DefaultFont", "FPS:\nFrame Time:\nEntities:\nCurrent Scene:", 24);
            titleTextComponent->SetStyle(sf::Text::Bold);

            this->overlayText->AddComponent("DebugText", std::unique_ptr<Components::Component>(titleTextComponent));
            this->entities.push_back(std::unique_ptr<Entity>(this->overlayText));
        }

        void DebugOverlayScene::UpdateBehavior(float deltaTime) {
            this->frameTimeAccumulator += deltaTime;
            if (this->frameTimeAccumulator >= 1.0f) {
                this->fps = 1.0f / deltaTime;
                this->frameTimeAccumulator = 0.0f;
            }
            this->frameTime = deltaTime * 1000.0f; // Convert to milliseconds

            this->entityCount = 0;
            if (this->engine_scenes) {
                std::stack<Scene*> temp = *this->engine_scenes;
                while (!temp.empty()) {
                    Scene* s = temp.top();
                    if (s) {
                        this->entityCount += static_cast<int>(s->entities.size());
                    }
                    temp.pop();
                }
            }

            if (this->engine_overlays) {
                for (Scene* overlay : *this->engine_overlays) {
                    if (overlay) {
                        this->entityCount += static_cast<int>(overlay->entities.size());
                    }
                }
            }

            std::string sceneName = "None";
            if (this->currentScene && *this->currentScene) {
                sceneName = typeid(**this->currentScene).name();
            }

            this->overlayText->GetComponent<Components::TextComponent>("DebugText")->SetText(
                "FPS: " + std::to_string(static_cast<int>(this->fps)) +
                "\nFrame Time: " + std::to_string(static_cast<int>(this->frameTime)) + " ms" +
                "\nEntities: " + std::to_string(this->entityCount) +
                "\nCurrent Scene: " + sceneName
            );
        }

        void DebugOverlayScene::HandleEvent(const std::optional<sf::Event>& event) {
            // Handle events for the debug overlay
        }

        void DebugOverlayScene::RenderBehavior() {
        }

    } // namespace OverlayScene
} // namespace Engine
