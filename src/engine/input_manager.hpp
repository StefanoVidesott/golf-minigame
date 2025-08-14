#pragma once

#include "resource_manager.hpp"

class InputManager {
public:
    void Update();
    void HandleEvents(const sf::Event& event);

    bool IsKeyDown(sf::Keyboard::Key key) const;
    bool IsKeyPressed(sf::Keyboard::Key key) const;
    bool IsKeyReleased(sf::Keyboard::Key key) const;

private:
    std::unordered_map<sf::Keyboard::Key, bool> keyDown;
    std::unordered_map<sf::Keyboard::Key, bool> keyPressed;
    std::unordered_map<sf::Keyboard::Key, bool> keyReleased;
};
