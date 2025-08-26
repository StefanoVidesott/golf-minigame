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

        void Scene::SetWindow(sf::RenderWindow* window) {
            this->window = window;
        }

        void Scene::SetActive(bool active) {
            this->active = active;
        }

        void Scene::SetVisible(bool visible) {
            this->visible = visible;
        }

        void Scene::SetGizmosEnabled(bool gizmosEnabled) {
            this->gizmosEnabled = gizmosEnabled;
        }

        bool Scene::IsActive() const {
            return this->active;
        }

        bool Scene::IsVisible() const {
            return this->visible;
        }

        bool Scene::AreGizmosEnabled() const {
            return this->gizmosEnabled;
        }

        std::vector<std::unique_ptr<Entity>> *Scene::GetEntityList() {
            return &this->entities;
        }

        int Scene::GetEntityCount() const {
            return static_cast<int>(this->entities.size());
        }

    } // namespace Scene
} // namespace Engine
