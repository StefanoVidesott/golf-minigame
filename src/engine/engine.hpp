#pragma once

#include "scene.hpp"
#include "debug_overlay.hpp"

namespace Engine {

    class Engine {
        public:
            Engine(sf::VideoMode, const std::string& = "Engine Window", unsigned int = sf::Style::Default);
            ~Engine();

            void Run();

            void SetWindowPosition(const sf::Vector2i&);

            void LoadScene(std::unique_ptr<Scene::Scene>);
            void DropScene();
        private:
            void Start();
            void HandleEvents();
            void Update();
            void Render();

            void InitResources();

            std::unique_ptr<sf::RenderWindow> window;
            sf::Clock deltaClock;
            float deltaTime;

            std::stack<std::unique_ptr<Scene::Scene>> scenes;
            std::vector<std::unique_ptr<Scene::Scene>> overlays;

            ResourceManager::TextureManager textureManager;
            ResourceManager::FontManager fontManager;
            ResourceManager::AudioManager audioManager;
            ResourceManager::SceneManager sceneManager;
            InputManager inputManager;
    };
};
