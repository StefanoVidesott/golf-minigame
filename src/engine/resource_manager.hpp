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

                void Initialize(std::stack<Scene::Scene*>*, std::vector<Scene::Scene*>*, Scene::Scene**);

                std::stack<Scene::Scene*> *GetScenes();
                std::vector<Scene::Scene*> *GetOverlays();
                Scene::Scene **GetCurrentScene();
            private:
                static std::stack<Scene::Scene*> *scenes;
                static std::vector<Scene::Scene*> *overlays;
                static Scene::Scene **currentScene;
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
