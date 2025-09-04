#include "dropdown.hpp"

namespace Engine {
    namespace Entities {

        Dropdown::Dropdown(std::vector<std::string> options, const std::string& selectedOption, const std::string& fontName, int fontSize, const sf::Vector2f& margin) {
            this->inputManager = Engine::ResourceManager::ResourceManager::GetInputManager();

            this->margin = margin;
            this->options = std::move(options);
            this->selectedOption = selectedOption.empty() && !this->options.empty() ? this->options.front() : selectedOption;

            std::string longestString;
            for (const auto& opt : this->options) {
                if (opt.size() > longestString.size()) {
                    longestString = opt;
                }
            }
            if (longestString.empty()) {
                longestString = "Select...";
            }

            this->mainButton = std::make_unique<TextButton>(longestString, [this]() { this->ToggleOpen(); }, fontName, fontSize);
            this->mainButton->EnableAutoBackgroundResize(false);
            this->mainButton->SetBackgroundColors(
                {100, 100, 100},
                {150, 150, 150},
                {200, 200, 200}
            );
            this->mainButton->SetTextString(this->selectedOption);

            for (const auto& opt : this->options) {
                auto button = std::make_unique<TextButton>(longestString, [this, opt]() { this->SelectOption(opt); }, fontName, fontSize);
                button->EnableAutoBackgroundResize(false);
                button->SetTextString(opt);
                button->SetBackgroundColors(
                    {100, 100, 100},
                    {150, 150, 150},
                    {200, 200, 200}
                );
                this->optionButtons.push_back(std::move(button));
            }

            this->LayoutOptions();
        }

        void Dropdown::LayoutOptions() {
            const auto mainBounds = this->mainButton->GetGlobalBounds();
            const float buttonHeight = mainBounds.size.y;

            const auto basePos = this->GetTransform()->GetPosition();
            this->mainButton->GetTransform()->SetPosition(basePos);

            for (size_t i = 0; i < this->optionButtons.size(); ++i) {
                this->optionButtons[i]->GetTransform()->SetPosition({
                    basePos.x,
                    basePos.y + (i + 1) * buttonHeight
                });
            }
        }

        bool Dropdown::UpdateInput(float dt) {
            bool status = this->mainButton->UpdateInput(dt);
            if (this->isOpen && !status) {
                for (auto& button : this->optionButtons) {
                    if (button->UpdateInput(dt)) {
                        status = true;
                    }
                }
            }
            return status;
        }

        void Dropdown::UpdateBehavior(float dt) {
            if (this->isOpen && this->inputManager->IsMouseButtonPressed(sf::Mouse::Button::Left)) {
                const auto mousePos = static_cast<sf::Vector2f>(this->inputManager->GetMousePosition());
                const auto mainBounds = this->mainButton->GetGlobalBounds();
                bool insideAnyButton = mainBounds.contains(mousePos);
                for (const auto& button : this->optionButtons) {
                    if (button->GetGlobalBounds().contains(mousePos)) {
                        insideAnyButton = true;
                        break;
                    }
                }
                if (!insideAnyButton) {
                    this->isOpen = false;
                }
            }
        }

        void Dropdown::RenderCustomBehavior(sf::RenderWindow* window) {
            this->mainButton->Render(window);
            if (this->isOpen) {
                for (auto& button : this->optionButtons) {
                    button->Render(window);
                }
            }
        }

        void Dropdown::ToggleOpen() {
            this->isOpen = !this->isOpen;
        }

        void Dropdown::SelectOption(const std::string& option) {
            this->selectedOption = option;
            this->mainButton->SetTextString(option);
            this->isOpen = false;
            if (this->onSelectionChanged) {
                this->onSelectionChanged(option);
            }
        }

        void Dropdown::SetOnSelectionChanged(std::function<void(const std::string&)> callback) {
            this->onSelectionChanged = std::move(callback);
        }

        void Dropdown::SetPosition(const sf::Vector2f& position) {
            this->GetTransform()->SetPosition(position);
            this->LayoutOptions();
        }

        void Dropdown::SetScale(const sf::Vector2f& scale) {
            this->GetTransform()->SetScale(scale);
            this->mainButton->GetTransform()->SetScale(scale);
            for (auto& button : this->optionButtons) {
                button->GetTransform()->SetScale(scale);
            }
            this->LayoutOptions();
        }

        void Dropdown::SetButtonTexture(const sf::Texture& texture) {
            this->mainButton->SetBackgroundTexture(texture);
            for (auto& button : this->optionButtons) {
                button->SetBackgroundTexture(texture);
            }
        }

        void Dropdown::SetButtonColors(const sf::Color& normal, const sf::Color& hover, const sf::Color& clicked) {
            this->mainButton->SetBackgroundColors(normal, hover, clicked);
            for (auto& button : this->optionButtons) {
                button->SetBackgroundColors(normal, hover, clicked);
            }
        }

    } // namespace Entities
} // namespace Engine
