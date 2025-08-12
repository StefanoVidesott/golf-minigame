#pragma once

#include "scene.hpp"

#include <SFML/Graphics.hpp>
#include <stack>

namespace Engine {

    class Engine {
        public:
            Engine();
            ~Engine();

            void LoadScene(Scene::Scene*);
            void DropScene();

            void Run();
        private:
            void Update();

            sf::RenderWindow *window;
            std::stack<Scene::Scene*> scenes; // List of scenes in the engine
            Scene::Scene *currentScene = nullptr; // Pointer to the currently active scene
            sf::Clock deltaClock;

            float fixedDeltaTime;
            float deltaTime;
        };
};
