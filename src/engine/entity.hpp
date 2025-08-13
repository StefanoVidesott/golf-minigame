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

        void AddComponent(Components::Component*);

        void Update(float);
        void Render(sf::RenderWindow*);
    private:
        std::vector<Components::Component*> components; // possible future implementation std::unordered_map<std::string, Components::Component*> components;
    };

} // namespace Engine