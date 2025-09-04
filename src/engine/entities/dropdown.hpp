#pragma once

#include "../entity.hpp"
#include "text_button.hpp"

namespace Engine {
    namespace Entities {

        class Dropdown : public Entity {
        public:
            Dropdown(std::vector<std::string> options = {}, const std::string& selectedOption = "", const std::string& fontName = "default", int fontSize = 30, const sf::Vector2f& margin = {20.f, 15.f});
            ~Dropdown() = default;

            bool UpdateInput(float dt) override;
            void RenderCustomBehavior(sf::RenderWindow*);

            void SetButtonTexture(const sf::Texture&);
            void SetButtonColors(const sf::Color&, const sf::Color&, const sf::Color&);

            void SetPosition(const sf::Vector2f& position);
            void SetScale(const sf::Vector2f& scale);

            [[nodiscard]] std::string GetSelectedOption() const { return selectedOption; }
            void SetOnSelectionChanged(std::function<void(const std::string&)> callback);

        private:
            void ToggleOpen();
            void SelectOption(const std::string& option);
            void LayoutOptions();

            InputManager* inputManager;

            bool isOpen {false};
            sf::Vector2f margin;
            std::vector<std::string> options;
            std::string selectedOption;

            std::unique_ptr<TextButton> mainButton;
            std::vector<std::unique_ptr<TextButton>> optionButtons;

            std::function<void(const std::string&)> onSelectionChanged;
        };

    } // namespace Entities
} // namespace Engine
