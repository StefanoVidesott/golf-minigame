#pragma once

#include <stack>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>

#include "include/base64.hpp"

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

        class AudioManager {
            public:
                AudioManager() = default;
                ~AudioManager() = default;

                void LoadSound(const std::string&, const std::string&);
                sf::SoundBuffer& GetSound(const std::string&);

                void LoadMusic(const std::string&, const std::string&);
                sf::Music& GetMusic(const std::string&);
                sf::Music* GetCurrentMusic();

                void SetCurrentMusic(const std::string&);
                void PlayMusic();
                void PauseMusic();
                void StopMusic();

            private:
                std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> sounds;
                std::unordered_map<std::string, std::unique_ptr<sf::Music>> music;
                sf::Music *currentMusic = nullptr;

                std::unordered_map<std::string, std::shared_ptr<std::vector<unsigned char>>> musicBlobs;
        };

        class SceneManager {
            public:
                SceneManager() = default;
                ~SceneManager() = default;

                void Initialize(std::stack<std::unique_ptr<Scene::Scene>>*, std::vector<std::unique_ptr<Scene::Scene>>*, std::function<void(std::unique_ptr<Scene::Scene>)>, std::function<void()>);

                void LoadScene(std::unique_ptr<Scene::Scene> scene);
                void DropScene();

                std::stack<std::unique_ptr<Scene::Scene>> *GetScenes();
                std::vector<std::unique_ptr<Scene::Scene>> *GetOverlays();
            private:
                std::stack<std::unique_ptr<Scene::Scene>> *scenes;
                std::vector<std::unique_ptr<Scene::Scene>> *overlays;

                std::function<void(std::unique_ptr<Scene::Scene>)> LoadSceneFunction;
                std::function<void()> DropSceneFunction;
        };

        class ResourceManager {
            public:
                ResourceManager() = default;
                ~ResourceManager() = default;

                static void SetWindow(sf::RenderWindow*);
                static sf::RenderWindow* GetWindow();

                static void SetTextureManager(TextureManager*);
                static TextureManager* GetTextureManager();

                static void SetFontManager(FontManager*);
                static FontManager* GetFontManager();

                static void SetAudioManager(AudioManager*);
                static AudioManager* GetAudioManager();

                static void SetSceneManager(SceneManager*);
                static SceneManager* GetSceneManager();

                static void SetInputManager(InputManager*);
                static InputManager* GetInputManager();

                static std::string NormalizePath(const std::string&);
                static std::shared_ptr<std::vector<unsigned char>> GetDecodedBlob(const std::string&);
            private:
                static std::unordered_map<std::string, std::shared_ptr<std::vector<unsigned char>>> g_decodedBlobs;

                static TextureManager* textureManager;
                static FontManager* fontManager;
                static AudioManager* audioManager;
                static SceneManager* sceneManager;
                static InputManager* inputManager;

                static sf::RenderWindow* window;

        };

    } // namespace ResourceManager
} // namespace Engine
