#include "text_component.hpp"

namespace Engine {
    namespace Components {

        TextComponent::TextComponent(const sf::Font& font, const std::string& text, unsigned int size) : text(font, text, size) {
        }

        TextComponent::TextComponent(const std::string fontName, const std::string& text, unsigned int size) : text(Engine::ResourceManager::ResourceManager::GetFont(fontName), text, size) {
        }

        void TextComponent::Update(float deltaTime) {
            // Update code here
        }

        void TextComponent::Render(sf::RenderWindow* window) {
            window->draw(this->text);
        }

        void TextComponent::SetPosition(const sf::Vector2f& position) {
            this->text.setPosition(position);
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

        [[nodiscard]] const sf::String& TextComponent::getString() const {
            return this->text.getString();
        }

        [[nodiscard]] const sf::Font* TextComponent::GetFont() const {
            return &this->text.getFont();
        }

        [[nodiscard]] unsigned int TextComponent::GetCharacterSize() const {
            return this->text.getCharacterSize();
        }

        [[nodiscard]] uint32_t TextComponent::GetStyle() const {
            return static_cast<uint32_t>(this->text.getStyle());
        }

        [[nodiscard]] sf::FloatRect TextComponent::GetGlobalBounds() const {
            return this->text.getGlobalBounds();
        }

    } // namespace Components
} // namespace Engine
