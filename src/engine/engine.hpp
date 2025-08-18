#pragma once

#include "scene.hpp"
#include "debug_overlay.hpp"

namespace Engine {

    class Engine {
        public:
            Engine();
            ~Engine();

            void Run();

            void LoadScene(std::unique_ptr<Scene::Scene>);
            void DropScene();
        private:
            void Start();
            void HandleEvents();
            void Update();
            void Render();

            void InitResources();

            sf::RenderWindow *window;
            sf::Clock deltaClock;
            float deltaTime;

            std::stack<std::unique_ptr<Scene::Scene>> scenes;
            std::vector<std::unique_ptr<Scene::Scene>> overlays;

            InputManager inputManager;
    };
};
