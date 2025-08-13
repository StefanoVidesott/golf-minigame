#pragma once

#include "components.hpp"

namespace Engine {
    namespace Components {
        class TextComponent : public Component {
        public:
            TextComponent();
            TextComponent(const sf::Font&, const std::string&, unsigned int);
            TextComponent(const std::string, const std::string&, unsigned int);
            ~TextComponent() override;

            void Update(float) override;
            void Render(sf::RenderWindow*) override;
        private:
            void InitializeText();
            sf::Text *text;
        };
    } // namespace Components
} // namespace Engine
