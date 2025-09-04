#pragma once

#include "../entity.hpp"

namespace Engine {
    namespace Entities {

        class Slider : public Entity {
        public:
            Slider(float minValue = 0.f, float maxValue = 1.f, float initialValue = 0.5f);
            ~Slider() = default;

            void UpdateBehavior(float dt) override;
            bool UpdateInput(float dt) override;

            // API
            void SetPosition(const sf::Vector2f& position);
            void SetSize(const sf::Vector2f& size);       // track size
            void SetHandleSize(const sf::Vector2f& size);

            void SetTrackColor(const sf::Color& color);
            void SetHandleColor(const sf::Color& color);
            void SetColors(const sf::Color& trackColor, const sf::Color& handleColor);
            void SetTrackTexture(const sf::Texture& texture);
            void SetHandleTexture(const sf::Texture& texture);

            void SetScale(const sf::Vector2f& scale);

            void SetRange(float minVal, float maxVal);
            void SetOnValueChanged(std::function<void(float)> callback);

            [[nodiscard]] float GetValue() const { return value; }
            void SetValue(float newValue);

        private:
            InputManager* inputManager {nullptr};

            Components::RectangleShapeComponent* track {nullptr};
            Components::RectangleShapeComponent* handle {nullptr};

            float minValue;
            float maxValue;
            float value;

            bool isDragging {false};

            std::function<void(float)> onValueChanged;

            void UpdateHandlePosition();
            float ValueFromMouse(float mouseX) const;
        };

    } // namespace Entities
} // namespace Engine
