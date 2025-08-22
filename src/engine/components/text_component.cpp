#include "text_component.hpp"

namespace Engine {
    namespace Components {

        // ---- Constructors ----

        TextComponent::TextComponent(const sf::Font& font, const std::string& text, unsigned int size) : text(font, text, size) {
        }

        TextComponent::TextComponent(const std::string fontName, const std::string& text, unsigned int size) : text(Engine::ResourceManager::ResourceManager::GetFont(fontName), text, size) {
        }

        // ---- Component Methods ----

        void TextComponent::Update(float deltaTime) {
        }

        void TextComponent::Render(sf::RenderWindow* window) {
            window->draw(this->text);
        }

        void TextComponent::SetPosition(const sf::Vector2f& position) {
            this->text.setPosition(position);
        }

        void TextComponent::SetRotation(sf::Angle angle) {
            this->text.setRotation(angle);
        }

        void TextComponent::SetScale(const sf::Vector2f& factors) {
            this->text.setScale(factors);
        }

        [[nodiscard]] sf::FloatRect TextComponent::GetGlobalBounds() const {
            return this->text.getGlobalBounds();
        }

        [[nodiscard]] sf::Vector2f TextComponent::GetOrigin() const {
            return this->text.getOrigin();
        }

        [[nodiscard]] sf::Vector2f TextComponent::GetPosition() const {
            return this->text.getPosition();
        }

        [[nodiscard]] sf::Angle TextComponent::GetRotation() const {
            return this->text.getRotation();
        }

        [[nodiscard]] sf::Vector2f TextComponent::GetScale() const {
            return this->text.getScale();
        }

        // ---- Text Methods ----

        void TextComponent::SetOrigin(const sf::Vector2f& origin) {
            this->text.setOrigin(origin);
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

        void TextComponent::SetFillColor(const sf::Color& color) {
            this->text.setFillColor(color);
        }

        void TextComponent::SetOutlineColor(const sf::Color& color) {
            this->text.setOutlineColor(color);
        }

        void TextComponent::SetOutlineThickness(float thickness) {
            this->text.setOutlineThickness(thickness);
        }

        [[nodiscard]] const sf::String& TextComponent::GetString() const {
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

    } // namespace Components
} // namespace Engine
