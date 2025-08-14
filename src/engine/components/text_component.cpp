#include "text_component.hpp"

namespace Engine {
    namespace Components {

        TextComponent::TextComponent(const sf::Font& font, const std::string& text, unsigned int size = 30) : text(font, text, size) {
        }

        TextComponent::TextComponent(const std::string fontName, const std::string& text, unsigned int size = 30) : text(Engine::ResourceManager::ResourceManager::getFont(fontName), text, size) {
        }

        void TextComponent::Update(float deltaTime) {
            // Update code here
        }

        void TextComponent::Render(sf::RenderWindow* window) {
            window->draw(text);
        }

    } // namespace Components
} // namespace Engine
