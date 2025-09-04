#include "entity.hpp"

namespace Engine {

    Entity::Entity() {
        this->transform.SetOwner(this);
    }

    Entity::~Entity() {
    }

    void Entity::AddComponent(std::string name, std::unique_ptr<Components::Component> component) {
        if (!component) {
            throw std::runtime_error("Null component");
        }
        component->SetOwner(this);
        components[name] = std::move(component);
        this->transform.UpdateEntityTransform();
    }

    void Entity::Update(float deltaTime) {
        for (const auto& component : components) {
            if (component.second) {
                component.second->Update(deltaTime);
            }
        }
        this->UpdateBehavior(deltaTime);
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
        this->RenderBehavior(window);
    }

    std::vector<Components::Component*> Entity::GetComponentList() {
        std::vector<Components::Component*> componentList;
        for (const auto& pair : components) {
            componentList.push_back(pair.second.get());
        }
        return componentList;
    }

    Components::TransformComponent *Entity::GetTransform() {
        return &this->transform;
    }

} // namespace Engine
