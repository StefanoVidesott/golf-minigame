#include "debug_overlay.hpp"

#if defined(__linux__)
    #include <unistd.h>
#elif defined(__APPLE__) && defined(__MACH__)
    #include <mach/mach.h>
#elif defined(_WIN32)
    #include <windows.h>
    #include <psapi.h>
#endif

namespace Engine {
    namespace OverlayScene {

        void DebugOverlayScene::Start() {
            this->Initialize();

            this->overlayText = new Entity();

            this->textComponent = new Components::TextComponent("DefaultFont", "FPS:\nFrame Time:\nEntities:\nCurrent Scene:", this->textSize);
            this->textComponent->SetStyle(sf::Text::Bold);
            this->overlayText->AddComponent("DebugText", std::unique_ptr<Components::Component>(this->textComponent));

            Components::RectangleShapeComponent* rectShape = new Components::RectangleShapeComponent(sf::Vector2f(230.0f, 113.0f));
            rectShape->SetFillColor(sf::Color(55, 55, 55, 150));
            rectShape->SetOutlineColor(sf::Color(70, 70, 70, 200));
            rectShape->SetOutlineThickness(3.0f);
            this->overlayText->AddComponent("DebugOverlayBackground", std::unique_ptr<Components::Component>(rectShape));

            this->entities.push_back(std::unique_ptr<Entity>(this->overlayText));
        }

        void DebugOverlayScene::Initialize() {
            this->active = true;
            this->visible = false;
            this->window = ResourceManager::ResourceManager::GetWindow();
            this->currentScene = ResourceManager::ResourceManager::sceneManager.GetCurrentScene();
            this->engine_scenes = ResourceManager::ResourceManager::sceneManager.GetScenes();
            this->engine_overlays = ResourceManager::ResourceManager::sceneManager.GetOverlays();
            this->inputManager = ResourceManager::ResourceManager::GetInputManager();
        }

        void DebugOverlayScene::UpdateBehavior(float deltaTime) {

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

            #elif defined(__APPLE__) && defined(__MACH__)
                #include <mach/mach.h>
                {
                    struct task_basic_info info;
                    mach_msg_type_number_t infoCount = TASK_BASIC_INFO_COUNT;
                    if (task_info(mach_task_self(), TASK_BASIC_INFO,
                                (task_info_t)&info, &infoCount) == KERN_SUCCESS) {
                        memoryUsage = std::to_string(info.resident_size / (1024 * 1024)) + " MB";
                    }
                }

            #elif defined(_WIN32)
                #include <windows.h>
                #include <psapi.h>
                {
                    PROCESS_MEMORY_COUNTERS pmc;
                    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
                        memoryUsage = std::to_string(pmc.WorkingSetSize / (1024 * 1024)) + " MB";
                    }
                }
            #endif

            std::string mousePosition = "N/A";
            if (this->inputManager) {
                sf::Vector2i mousePos = this->inputManager->GetMousePosition();
                mousePosition = "(" + std::to_string(mousePos.x) + ", " + std::to_string(mousePos.y) + ")";
            }

            char buffer[256];
            snprintf(buffer, sizeof(buffer),
                "FPS: %.1f\n"
                "Frame Time: %.2f ms\n"
                "Entities: %d\n"
                "Current Scene: %s\n"
                "Memory Usage: %s\n"
                "Mouse Position: %s",
                this->fps, frameTimeMs,
                this->entityCount,
                sceneName.c_str(),
                memoryUsage.c_str(),
                mousePosition.c_str()
            );

            this->textComponent->SetText(buffer);
        }


        void DebugOverlayScene::HandleEvent(const std::optional<sf::Event>& event) {
            if (this->inputManager) {
                this->inputManager->IsKeyPressed(sf::Keyboard::Key::F3) ? this->visible = !this->visible : false;
            }
        }

        void DebugOverlayScene::RenderBehavior() {
        }

        std::string DebugOverlayScene::GetName() const {
            return "DebugOverlayScene";
        }

    } // namespace OverlayScene
} // namespace Engine
