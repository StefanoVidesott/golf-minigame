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
            window->draw(this->text);
        }

        void TextComponent::SetText(const std::string& newText) {
            this->text.setString(newText);
        }

        void TextComponent::SetFont(const sf::Font& font) {
            this->text.setFont(font);
        }

        void TextComponent::SetCharacterSize(unsigned int size) {
            this->text.setCharacterSize(size);
        }

        void TextComponent::SetStyle(sf::Text::Style style) {
            this->text.setStyle(style);
        }

        const std::string& TextComponent::getString() const {
            return this->text.getString();
        }

        const sf::Font* TextComponent::GetFont() const {
            return &this->text.getFont();
        }

        unsigned int TextComponent::GetCharacterSize() const {
            return this->text.getCharacterSize();
        }

        uint32_t TextComponent::GetStyle() const {
            return static_cast<uint32_t>(this->text.getStyle());
        }

    } // namespace Components
} // namespace Engine
