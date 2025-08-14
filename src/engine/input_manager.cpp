#include "input_manager.hpp"

void InputManager::Update() {
    keyPressed.clear();
    keyReleased.clear();
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
