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
                void SetMusicVolume(float);
                float GetMusicVolume() const { return musicVolume; }

            private:
                std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> sounds;
                std::unordered_map<std::string, std::unique_ptr<sf::Music>> music;
                sf::Music *currentMusic = nullptr;
                float musicVolume = 100.f;

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

        class SettingsManager {
            public:
                SettingsManager(const std::string &file_path = "settings.ini") {
                    SetConfigFilePath(file_path);
                }
                ~SettingsManager() = default;

                void LoadSettings();
                void SaveSettings() const;

                template <typename T>
                T Get(const std::string& key, const T& fallback = T{}) const;

                template <typename T>
                void Set(const std::string& key, const T& value);

                void SetConfigFilePath(const std::string& path) {
                    this->configFilePath = path;
                }

                void ApplySettings();
                void ApplyVideoSettings();
                void ApplyWindowSize();
                void ApplyAudioSettings();
            private:
                void InitDefaultSettings();

                std::string configFilePath;
                std::unordered_map<std::string, std::string> settings;
        };


        // ---------------------------
        // template specializations
        // ---------------------------

        // string
        template <>
        inline std::string SettingsManager::Get<std::string>(
            const std::string& key, const std::string& fallback) const {
            auto it = settings.find(key);
            return (it != settings.end()) ? it->second : fallback;
        }
        template <>
        inline void SettingsManager::Set<std::string>(
            const std::string& key, const std::string& value) {
            settings[key] = value;
        }

        // int
        template <>
        inline int SettingsManager::Get<int>(
            const std::string& key, const int& fallback) const {
            auto it = settings.find(key);
            if (it != settings.end()) {
                try { return std::stoi(it->second); }
                catch (...) { return fallback; }
            }
            return fallback;
        }
        template <>
        inline void SettingsManager::Set<int>(
            const std::string& key, const int& value) {
            settings[key] = std::to_string(value);
        }

        // float
        template <>
        inline float SettingsManager::Get<float>(
            const std::string& key, const float& fallback) const {
            auto it = settings.find(key);
            if (it != settings.end()) {
                try { return std::stof(it->second); }
                catch (...) { return fallback; }
            }
            return fallback;
        }
        template <>
        inline void SettingsManager::Set<float>(
            const std::string& key, const float& value) {
            settings[key] = std::to_string(value);
        }

        // bool
        template <>
        inline bool SettingsManager::Get<bool>(
            const std::string& key, const bool& fallback) const {
            auto it = settings.find(key);
            if (it != settings.end()) {
                std::string val = it->second;
                std::transform(val.begin(), val.end(), val.begin(), ::tolower);
                if (val == "true" || val == "1" || val == "yes") return true;
                if (val == "false" || val == "0" || val == "no") return false;
            }
            return fallback;
        }
        template <>
        inline void SettingsManager::Set<bool>(
            const std::string& key, const bool& value) {
            settings[key] = value ? "true" : "false";
        }

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

                static SettingsManager* GetSettingsManager();
                static void SetSettingsManager(SettingsManager*);

                static std::string NormalizePath(const std::string&);
                static std::shared_ptr<std::vector<unsigned char>> GetDecodedBlob(const std::string&);
            private:
                static std::unordered_map<std::string, std::shared_ptr<std::vector<unsigned char>>> g_decodedBlobs;

                static TextureManager* textureManager;
                static FontManager* fontManager;
                static AudioManager* audioManager;
                static SceneManager* sceneManager;
                static InputManager* inputManager;
                static SettingsManager* settingsManager;

                static sf::RenderWindow* window;

        };

    } // namespace ResourceManager
} // namespace Engine
