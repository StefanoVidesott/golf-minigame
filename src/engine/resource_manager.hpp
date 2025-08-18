#pragma once

#include <stack>
#include <memory>
#include <string>
#include <iostream>
#include <stdexcept>
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

                void loadTexture(const std::string&, const std::string&);
                sf::Texture& getTexture(const std::string&);
            private:
                std::unordered_map<std::string, std::unique_ptr<sf::Texture>> textures;
        };

        class FontManager {
            public:
                FontManager() = default;
                ~FontManager() = default;

                void loadFont(const std::string&, const std::string&);
                sf::Font& getFont(const std::string&);

            private:
                std::unordered_map<std::string, std::unique_ptr<sf::Font>> fonts;
        };

        class SceneManager {
            public:
                SceneManager() = default;
                ~SceneManager() = default;

                void Initialize(std::stack<std::unique_ptr<Scene::Scene>>*, std::vector<std::unique_ptr<Scene::Scene>>*);

                std::stack<std::unique_ptr<Scene::Scene>> *GetScenes();
                std::vector<std::unique_ptr<Scene::Scene>> *GetOverlays();
            private:
                static std::stack<std::unique_ptr<Scene::Scene>> *scenes;
                static std::vector<std::unique_ptr<Scene::Scene>> *overlays;
        };

        class ResourceManager {
            public:
                ResourceManager() = default;
                ~ResourceManager() = default;

                static void loadTexture(const std::string&, const std::string&);
                static sf::Texture& getTexture(const std::string&);

                static void loadFont(const std::string&, const std::string&);
                static sf::Font& getFont(const std::string&);

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
