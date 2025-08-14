#include "entity.hpp"

namespace Engine {

    Entity::Entity() {
        // Constructor implementation can be added here if needed
    }

    Entity::~Entity() {
        components.clear();
    }

    void Entity::AddComponent(std::unique_ptr<Components::Component> component) {
        if (!component){
            throw std::runtime_error("Null component");
        }
        components.push_back(std::move(component));
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