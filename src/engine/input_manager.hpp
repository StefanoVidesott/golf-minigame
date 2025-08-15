#pragma once

#include "resource_manager.hpp"

namespace Engine {
    class InputManager {
        public:
            void Update();
            void HandleEvents(const sf::Event& event);

            bool IsKeyDown(sf::Keyboard::Key key) const;
            bool IsKeyPressed(sf::Keyboard::Key key) const;
            bool IsKeyReleased(sf::Keyboard::Key key) const;

            // Mouse position
            sf::Vector2i GetMousePosition() const;

        private:
            std::unordered_map<sf::Keyboard::Key, bool> keyDown;
            std::unordered_map<sf::Keyboard::Key, bool> keyPressed;
            std::unordered_map<sf::Keyboard::Key, bool> keyReleased;
    };
} // namespace Engine
