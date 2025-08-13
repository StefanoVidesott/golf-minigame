#include "entity.hpp"

namespace Engine {

    Entity::Entity() {
        // Constructor implementation can be added here if needed
    }

    Entity::~Entity() {
        // Destructor implementation can be added here if needed
        for (auto& component : components) {
            delete component; // Clean up dynamically allocated components
        }
    }

    void Entity::AddComponent(Components::Component* component) {
        if (component) {
            components.push_back(component);
        } else {
            throw std::runtime_error("Attempted to add a null component to the entity.");
        }
    }

    void Entity::Update(float deltaTime) {
        for (auto& component : components) {
            component->Update(deltaTime);
        }
    }

    void Entity::Render(sf::RenderWindow* window) {
        if (!window) {
            throw std::runtime_error("RenderWindow pointer is null");
        }
        else {
            for (auto& component : components) {
                component->Render(window);
            }
        }
    }

} // namespace Engine