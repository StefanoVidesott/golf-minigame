#include "entity.hpp"

namespace Engine {

    Entity::Entity() {
        // Constructor implementation can be added here if needed
    }

    Entity::~Entity() {
    }

    void Entity::AddComponent(std::string name, std::unique_ptr<Components::Component> component) {
        if (!component) {
            throw std::runtime_error("Null component");
        }
        components[name] = std::move(component);
    }

    void Entity::Update(float deltaTime) {
        for (const auto& component : components) {
            if (component.second) {
                component.second->Update(deltaTime);
            }
        }
    }

    void Entity::Render(sf::RenderWindow* window) {
        if (!window) {
            throw std::runtime_error("RenderWindow pointer is null");
        }
        else {
            for (auto& component : components) {
                if (component.second) {
                    component.second->Render(window);
                }
            }
        }
    }

} // namespace Engine
