#include "scene.hpp"

namespace Engine {
    namespace Scene {

        void Scene::Update(float deltaTime) {
            this->UpdateBehavior(deltaTime);
            for (std::unique_ptr<Entity>& entity : entities) {
                if (entity) {
                    entity->Update(deltaTime);
                }
            }
        }

        void Scene::Render() {
            if (!this->window) {
                throw std::runtime_error("Render window is not initialized");
            }
            for (const std::unique_ptr<Entity>& entity : entities) {
                if (entity) {
                    entity->Render(this->window);
                }
            }

            this->RenderBehavior();
        }

        void Scene::ToggleGizmos() {
            this->gizmosEnabled = !this->gizmosEnabled;
            for (const std::unique_ptr<Entity>& entity : entities) {
                if (entity) {
                    for (Components::Component* component : entity->GetComponentList()) {
                        if (component) {
                            component->SetGizmoEnabled(this->gizmosEnabled);
                        }
                    }
                }
            }
        }

    } // namespace Scene
} // namespace Engine
