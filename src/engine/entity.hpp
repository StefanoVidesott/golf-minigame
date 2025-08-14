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

        void AddComponent(std::unique_ptr<Components::Component>);

        void Update(float);
        void Render(sf::RenderWindow*);
    private:
        std::vector<std::unique_ptr<Components::Component>> components;
    };

} // namespace Engine