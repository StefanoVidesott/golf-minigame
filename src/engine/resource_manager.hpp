#pragma once

#include <stack>
#include <memory>
#include <string>
#include <iostream>
#include <stdexcept>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <SFML/Graphics.hpp>

namespace Engine {
    class InputManager;

    namespace Scene {
        class Scene;
    }

    namespace ResourceManager {

        class TextureManager {
            public:
                TextureManager() = default;
                ~TextureManager() = default;

                void LoadTexture(const std::string&, const std::string&);
                sf::Texture& GetTexture(const std::string&);
            private:
                std::unordered_map<std::string, std::unique_ptr<sf::Texture>> textures;
        };

        class FontManager {
            public:
                FontManager() = default;
                ~FontManager() = default;

                void LoadFont(const std::string&, const std::string&);
                sf::Font& GetFont(const std::string&);

            private:
                std::unordered_map<std::string, std::unique_ptr<sf::Font>> fonts;
        };

        class SceneManager {
            public:
                SceneManager() = default;
                ~SceneManager() = default;

                void Initialize(std::stack<std::unique_ptr<Scene::Scene>>*, std::vector<std::unique_ptr<Scene::Scene>>*, std::function<void(std::unique_ptr<Scene::Scene>)>, std::function<void()>);

                static void LoadScene(std::unique_ptr<Scene::Scene> scene);
                static void DropScene();

                std::stack<std::unique_ptr<Scene::Scene>> *GetScenes();
                std::vector<std::unique_ptr<Scene::Scene>> *GetOverlays();
            private:
                static std::stack<std::unique_ptr<Scene::Scene>> *scenes;
                static std::vector<std::unique_ptr<Scene::Scene>> *overlays;

                static std::function<void(std::unique_ptr<Scene::Scene>)> LoadSceneFunction;
                static std::function<void()> DropSceneFunction;
        };

        class ResourceManager {
            public:
                ResourceManager() = default;
                ~ResourceManager() = default;

                static void LoadTexture(const std::string&, const std::string&);
                static sf::Texture& GetTexture(const std::string&);

                static void LoadFont(const std::string&, const std::string&);
                static sf::Font& GetFont(const std::string&);

                static void SetWindow(sf::RenderWindow*);
                static sf::RenderWindow* GetWindow();

                static InputManager* SetInputManager(InputManager*);
                static InputManager* GetInputManager();

                static SceneManager sceneManager;
            private:
                static TextureManager textureManager;
                static FontManager fontManager;

                static sf::RenderWindow* window;
                static InputManager* inputManager;
        };

    } // namespace ResourceManager
} // namespace Engine
