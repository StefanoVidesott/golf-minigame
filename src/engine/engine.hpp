#pragma once

#include "scene.hpp"
#include "debug_overlay.hpp"

namespace Engine {

    class Engine {
        public:
            Engine();
            ~Engine();

            void Run();

            void LoadScene(Scene::Scene*);
            void DropScene();
        private:
            void Start();
            void HandleEvents();
            void Update();
            void Render();

            sf::RenderWindow *window;
            Scene::Scene *currentScene = nullptr;
            sf::Clock deltaClock;
            float deltaTime;

            std::stack<Scene::Scene*> scenes;
            std::vector<Scene::Scene*> overlays;

            InputManager inputManager;
    };
};
