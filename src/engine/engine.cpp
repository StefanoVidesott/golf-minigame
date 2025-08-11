#include "engine.hpp"

namespace Engine {

    Engine::Engine() {
        this->window = new sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Golf-Minigame");
        this->window->setFramerateLimit(144);
    }

    Engine::~Engine() {
        delete window;
    }

    void Engine::LoadScene(Scene::Scene *scene) {
        if (scene) {
            scene->Start();
            this->scenes.push(scene);
            scene->loaded = true;
            scene->active = true;
            scene->window = this->window;
            this->currentScene->active = false;
            this->currentScene = scene;
        }
    }

    void Engine::DropScene() {
        if (currentScene) {
            currentScene->active = false;
            this->scenes.pop();
            currentScene = this->scenes.top();
            currentScene->active = true;
        }
    }

    void Engine::Run() {
        this->Update();
    }

    void Engine::Update() {
        while (this->window->isOpen())
        {
            if(currentScene) {
                this->fixedDeltaTime = this->deltaClock.reset().asSeconds();
                this->currentScene->FixedUpdate(this->fixedDeltaTime);
                this->deltaTime = this->fixedDeltaTime + this->deltaClock.restart().asSeconds();
                this->currentScene->Update(this->deltaTime);

                while (const std::optional event = this->window->pollEvent())
                {
                    if (event->is<sf::Event::Closed>())
                    {
                        this->window->close();
                    }
                    this->currentScene->HandleEvent(event);
                }

                this->window->clear();
                this->currentScene->Render();
                this->window->display();
            }
            else {
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

    }

}
