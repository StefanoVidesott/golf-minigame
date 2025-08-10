#include "engine.hpp"

namespace Engine {

    Engine::Engine() {
        this->window = new sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Golf-Minigame");
        this->window->setFramerateLimit(144);
    }

    Engine::~Engine() {
        delete window;
    }

    void Engine::Run() {
        this->Update();
    }

    void Engine::Update() {
        while (this->window->isOpen())
        {
            while (const std::optional event = this->window->pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                {
                    this->window->close();
                }
            }

            this->window->clear();
            this->window->display();
        }

    }

};
