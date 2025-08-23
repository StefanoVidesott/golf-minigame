#include "input_manager.hpp"

namespace Engine {

    void InputManager::Update() {
        // azzera gli eventi "one–frame"
        keyPressed.clear();
        keyReleased.clear();
        mouseButtonPressed.clear();
        mouseButtonReleased.clear();
    }

    void InputManager::HandleEvents(const sf::Event& event) {
        if (event.is<sf::Event::KeyPressed>()) {
            auto key = event.getIf<sf::Event::KeyPressed>()->code;
            if (!keyDown[key]) {
                keyPressed[key] = true;
            }
            keyDown[key] = true;
        }
        else if (event.is<sf::Event::KeyReleased>()) {
            auto key = event.getIf<sf::Event::KeyReleased>()->code;
            keyReleased[key] = true;
            keyDown[key] = false;
        }

        if (event.is<sf::Event::MouseButtonPressed>()) {
            auto button = event.getIf<sf::Event::MouseButtonPressed>()->button;
            if (!mouseButtonDown[button]) {
                mouseButtonPressed[button] = true;
            }
            mouseButtonDown[button] = true;
        }
        else if (event.is<sf::Event::MouseButtonReleased>()) {
            auto button = event.getIf<sf::Event::MouseButtonReleased>()->button;
            mouseButtonReleased[button] = true;
            mouseButtonDown[button] = false;
        }
    }

    bool InputManager::IsKeyDown(sf::Keyboard::Key key) const {
        auto it = keyDown.find(key);
        return it != keyDown.end() && it->second;
    }

    bool InputManager::IsKeyPressed(sf::Keyboard::Key key) const {
        return keyPressed.count(key) > 0;
    }

    bool InputManager::IsKeyReleased(sf::Keyboard::Key key) const {
        return keyReleased.count(key) > 0;
    }

    sf::Vector2i InputManager::GetMousePosition() const {
        return sf::Mouse::getPosition(*ResourceManager::ResourceManager::GetWindow());
    }

    bool InputManager::IsMouseButtonDown(sf::Mouse::Button button) const {
        auto it = mouseButtonDown.find(button);
        return it != mouseButtonDown.end() && it->second;
    }

    bool InputManager::IsMouseButtonPressed(sf::Mouse::Button button) const {
        return mouseButtonPressed.count(button) > 0;
    }

    bool InputManager::IsMouseButtonReleased(sf::Mouse::Button button) const {
        return mouseButtonReleased.count(button) > 0;
    }

} // namespace Engine
