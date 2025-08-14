#include "scene.hpp"

namespace Engine {
    namespace Scene {

        Scene::~Scene() {
            entities.clear();
        }

        void Scene::Update(float deltaTime) {
            this->UpdateBehavior(deltaTime);
            for (std::unique_ptr<Entity>& entity : entities) {
                if (entity) {
                    entity->Update(deltaTime);
                }
            }
        }

        void Scene::Render() {
            this->RenderBehavior();

            if (!this->window) {
                throw std::runtime_error("Render window is not initialized");
                return; // Ensure the window is valid before rendering
            }
            for (const std::unique_ptr<Entity>& entity : entities) {
                if (entity) {
                    entity->Render(this->window);
                }
            }
        }

    } // namespace Scene
} // namespace Engine
