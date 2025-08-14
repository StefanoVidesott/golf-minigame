#pragma once

#include "components.hpp"

namespace Engine {
    namespace Components {
        class TextComponent : public Component {
        public:
            TextComponent(const sf::Font&, const std::string&, unsigned int);
            TextComponent(const std::string, const std::string&, unsigned int);
            ~TextComponent() override = default;

            void Update(float) override;
            void Render(sf::RenderWindow*) override;
        private:
            sf::Text text;
        };
    } // namespace Components
} // namespace Engine
