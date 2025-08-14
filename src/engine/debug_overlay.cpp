#include "debug_overlay.hpp"

#if defined(__linux__)
#include <unistd.h>
#endif

namespace Engine {
    namespace OverlayScene {

        void DebugOverlayScene::Start() {
            this->overlayText = new Entity();
            Components::TextComponent *titleTextComponent = new Components::TextComponent("DefaultFont", "FPS:\nFrame Time:\nEntities:\nCurrent Scene:", 16);
            titleTextComponent->SetStyle(sf::Text::Bold);

            this->overlayText->AddComponent("DebugText", std::unique_ptr<Components::Component>(titleTextComponent));
            this->entities.push_back(std::unique_ptr<Entity>(this->overlayText));
        }

        void DebugOverlayScene::UpdateBehavior(float deltaTime) {
            static unsigned long long totalFrames = 0;
            totalFrames++;

            constexpr float smoothing = 0.1f;
            if (this->fps == 0.0f) {
                this->fps = 1.0f / deltaTime;
                this->frameTime = deltaTime;
            } else {
                this->fps = (1.0f / deltaTime) * smoothing + this->fps * (1.0f - smoothing);
                this->frameTime = deltaTime * smoothing + this->frameTime * (1.0f - smoothing);
            }

            // conversione frame time in ms
            float frameTimeMs = this->frameTime * 1000.0f;

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
                sceneName = (*this->currentScene)->GetName();
            }

            std::string memoryUsage = "N/A";
            #if defined(__linux__)
                {
                    FILE* file = fopen("/proc/self/statm", "r");
                    if (file) {
                        long rss;
                        if (fscanf(file, "%*s%ld", &rss) == 1) {
                            long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024;
                            long mem_kb = rss * page_size_kb;
                            memoryUsage = std::to_string(mem_kb / 1024) + " MB";
                        }
                        fclose(file);
                    }
                }
            #endif

            char buffer[256];
            snprintf(buffer, sizeof(buffer),
                "FPS: %.1f\n"
                "Frame Time: %.2f ms\n"
                "Entities: %d\n"
                "Current Scene: %s\n"
                "Frames Rendered: %llu\n"
                "Memory Usage: %s",
                this->fps, frameTimeMs,
                this->entityCount,
                sceneName.c_str(),
                totalFrames,
                memoryUsage.c_str()
            );

            Components::TextComponent *textComp = this->overlayText->GetComponent<Components::TextComponent>("DebugText");
            if (textComp) {
                textComp->SetText(buffer);
            }
        }


        void DebugOverlayScene::HandleEvent(const std::optional<sf::Event>& event) {
            // Handle events for the debug overlay
        }

        void DebugOverlayScene::RenderBehavior() {
        }

        std::string DebugOverlayScene::GetName() const {
            return "DebugOverlayScene";
        }

    } // namespace OverlayScene
} // namespace Engine
