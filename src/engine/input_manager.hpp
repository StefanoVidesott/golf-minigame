#pragma once

#include "resource_manager.hpp"

namespace Engine {
    class InputManager {
        public:
            void Update();
            void HandleEvents(const sf::Event&);

            bool IsKeyDown(sf::Keyboard::Key) const;
            bool IsKeyPressed(sf::Keyboard::Key) const;
            bool IsKeyReleased(sf::Keyboard::Key) const;

            bool IsMouseButtonDown(sf::Mouse::Button) const;
            bool IsMouseButtonPressed(sf::Mouse::Button) const;
            bool IsMouseButtonReleased(sf::Mouse::Button) const;

            // Mouse position
            sf::Vector2i GetMousePosition() const;

        private:
            std::unordered_map<sf::Keyboard::Key, bool> keyDown;
            std::unordered_map<sf::Keyboard::Key, bool> keyPressed;
            std::unordered_map<sf::Keyboard::Key, bool> keyReleased;

            std::unordered_map<sf::Mouse::Button, bool> mouseButtonDown;
            std::unordered_map<sf::Mouse::Button, bool> mouseButtonPressed;
            std::unordered_map<sf::Mouse::Button, bool> mouseButtonReleased;
    };
} // namespace Engine
