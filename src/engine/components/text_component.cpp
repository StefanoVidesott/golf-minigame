#include "text_component.hpp"

namespace Engine {
    namespace Components {

        TextComponent::TextComponent() {
        }

        TextComponent::TextComponent(const sf::Font& font, const std::string& text, unsigned int size = 30) {
            this->text = new sf::Text(font, text, size);
        }

        TextComponent::TextComponent(const std::string fontName, const std::string& text, unsigned int size = 30) {
            sf::Font& font = Engine::ResourceManager::ResourceManager::getFont(fontName);
            this->text = new sf::Text(font, text, size);
        }

        TextComponent::~TextComponent() {
            delete text;
        }

        void TextComponent::InitializeText() {
            text = new sf::Text(Engine::ResourceManager::ResourceManager::getFont("DefaultFont"), "TextComponent", 30);
            text->setFillColor(sf::Color::White);
        }

        void TextComponent::Update(float deltaTime) {
            // Update code here
        }

        void TextComponent::Render(sf::RenderWindow* window) {
            window->draw(*text);
        }

    } // namespace Components
} // namespace Engine
