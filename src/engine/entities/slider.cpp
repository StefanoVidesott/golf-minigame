#include "slider.hpp"
#include "../resource_manager.hpp"

namespace Engine {
    namespace Entities {

        Slider::Slider(float minValue, float maxValue, float initialValue)
            : minValue(minValue), maxValue(maxValue), value(initialValue)
        {
            this->inputManager = Engine::ResourceManager::ResourceManager::GetInputManager();

            auto trackPtr = std::make_unique<Components::RectangleShapeComponent>();
            this->track = trackPtr.get();
            this->AddComponent("Track", std::move(trackPtr));

            auto handlePtr = std::make_unique<Components::RectangleShapeComponent>();
            this->handle = handlePtr.get();
            this->AddComponent("Handle", std::move(handlePtr));

            this->track->SetSize({200.f, 6.f});
            this->track->SetFillColor(sf::Color(150,150,150));
            this->track->SetOrigin({0.f, this->track->GetSize().y / 2.f});

            this->handle->SetSize({14.f, 20.f});
            this->handle->SetFillColor(sf::Color::White);
            this->handle->SetOrigin(this->handle->GetSize() / 2.f);

            UpdateHandlePosition();
        }

        void Slider::SetPosition(const sf::Vector2f& position) {
            this->GetTransform()->SetPosition(position);
            this->track->SetPosition(position);
            UpdateHandlePosition();
        }

        void Slider::SetSize(const sf::Vector2f& size) {
            this->track->SetSize(size);
            this->track->SetOrigin({0.f, size.y / 2.f});
            UpdateHandlePosition();
        }

        void Slider::SetHandleSize(const sf::Vector2f& size) {
            this->handle->SetSize(size);
            this->handle->SetOrigin(size / 2.f);
            UpdateHandlePosition();
        }

        void Slider::SetTrackColor(const sf::Color& color) {
            this->track->SetFillColor(color);
        }

        void Slider::SetHandleColor(const sf::Color& color) {
            this->handle->SetFillColor(color);
        }

        void Slider::SetColors(const sf::Color& trackColor, const sf::Color& handleColor) {
            SetTrackColor(trackColor);
            SetHandleColor(handleColor);
        }

        void Slider::SetRange(float minVal, float maxVal) {
            this->minValue = minVal;
            this->maxValue = maxVal;
            SetValue(value); // riclampare
        }

        void Slider::SetValue(float newValue) {
            value = std::clamp(newValue, minValue, maxValue);
            UpdateHandlePosition();
            if (onValueChanged) onValueChanged(value);
        }

        void Slider::UpdateHandlePosition() {
            sf::FloatRect bounds = this->track->GetGlobalBounds();

            float ratio = (value - minValue) / (maxValue - minValue);

            float x = bounds.position.x + ratio * bounds.size.x;
            float y = bounds.position.y + bounds.size.y / 2.f;

            this->handle->SetPosition({x, y});
        }

        float Slider::ValueFromMouse(float mouseX) const {
            sf::FloatRect bounds = this->track->GetGlobalBounds();

            float ratio = (mouseX - bounds.position.x) / bounds.size.x;
            ratio = std::clamp(ratio, 0.f, 1.f);

            return minValue + ratio * (maxValue - minValue);
        }


        bool Slider::UpdateInput(float dt) {
            sf::Vector2f mousePos = static_cast<sf::Vector2f>(inputManager->GetMousePosition());
            bool contains = this->handle->GetGlobalBounds().contains(mousePos);

            if (inputManager->IsMouseButtonDown(sf::Mouse::Button::Left)) {
                if (!isDragging && contains) {
                    isDragging = true;
                }
            } else {
                isDragging = false;
            }

            if (isDragging) {
                float newVal = ValueFromMouse(mousePos.x);
                if (newVal != value) {
                    value = newVal;
                    UpdateHandlePosition();
                    if (onValueChanged) onValueChanged(value);
                }
                return true; // input consumato
            }

            return contains;
        }

        void Slider::UpdateBehavior(float dt) {
            // placeholder per animazioni
        }

        void Slider::SetOnValueChanged(std::function<void(float)> callback) {
            this->onValueChanged = std::move(callback);
        }

        void Slider::SetScale(const sf::Vector2f& scale) {
            this->GetTransform()->SetScale(scale);
            this->track->SetScale(scale);
            this->handle->SetScale(scale);
            UpdateHandlePosition();
        }

    } // namespace Entities
} // namespace Engine
