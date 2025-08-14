#pragma once

#include "scene.hpp"

namespace Engine {

    class Engine {
        public:
            Engine();
            ~Engine();

            void LoadScene(Scene::Scene*);
            void DropScene();

            void Run();
        private:
            void Start();
            void Update();

            sf::RenderWindow *window;
            std::stack<Scene::Scene*> scenes;
            Scene::Scene *currentScene = nullptr;
            sf::Clock deltaClock;

            float deltaTime;
    };
};
