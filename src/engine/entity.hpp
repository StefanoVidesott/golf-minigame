#pragma once

#include <optional>
#include <SFML/Graphics.hpp>
#include "components/components.hpp"

#include "components/text_component.hpp"

namespace Engine {

    class Entity {
    public:
        Entity();
        ~Entity();

        void AddComponent(std::string, std::unique_ptr<Components::Component>);

        template <typename T>
        T* GetComponent(const std::string& name) {
            auto it = components.find(name);
            if (it != components.end()) {
                return dynamic_cast<T*>(it->second.get());
            }
            return nullptr;
        }

        void Update(float);
        void Render(sf::RenderWindow*);
    private:
        std::unordered_map<std::string, std::unique_ptr<Components::Component>> components;
    };

} // namespace Engine
