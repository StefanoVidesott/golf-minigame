#include "resource_manager.hpp"

namespace Engine {
    namespace ResourceManager {

        // ---- TEXTURE MANAGER ----

        void TextureManager::LoadTexture(const std::string& name, const std::string& filePath) {
            std::unique_ptr<sf::Texture> texturePtr(new sf::Texture());

            if (!texturePtr->loadFromFile(filePath)) {
                throw std::runtime_error("Failed to load texture: " + filePath);
            }

            textures[name] = std::move(texturePtr);
        }

        sf::Texture& TextureManager::GetTexture(const std::string& name) {
            std::unordered_map<std::string, std::unique_ptr<sf::Texture>>::iterator it = textures.find(name);
            if (it != textures.end()) return *(it->second);

            std::unordered_map<std::string, std::unique_ptr<sf::Texture>>::iterator def = textures.find("DefaultTexture");
            if (def != textures.end()) return *(def->second);

            throw std::runtime_error("Texture not found: " + name + " (and DefaultTexture missing)");
        }

        // ---- FONT MANAGER ----

        void FontManager::LoadFont(const std::string& name, const std::string& filePath) {
            std::unique_ptr<sf::Font> fontPtr(new sf::Font());

            if (!fontPtr->openFromFile(filePath)) {
                throw std::runtime_error("Failed to load font: " + filePath);
            }

            fonts[name] = std::move(fontPtr);
        }

        sf::Font& FontManager::GetFont(const std::string& name) {
            std::unordered_map<std::string, std::unique_ptr<sf::Font>>::iterator it = fonts.find(name);
            if (it != fonts.end()) return *(it->second);

            std::unordered_map<std::string, std::unique_ptr<sf::Font>>::iterator def = fonts.find("DefaultFont");
            if (def != fonts.end()) return *(def->second);

            throw std::runtime_error("Font not found: " + name + " (and DefaultFont missing)");
        }

        // ---- SCENE MANAGER ----
        std::stack<std::unique_ptr<Scene::Scene>> *SceneManager::scenes = nullptr;
        std::vector<std::unique_ptr<Scene::Scene>> *SceneManager::overlays = nullptr;

        void SceneManager::Initialize(std::stack<std::unique_ptr<Scene::Scene>>* scenesPtr, std::vector<std::unique_ptr<Scene::Scene>>* overlaysPtr) {
            SceneManager::scenes = scenesPtr;
            SceneManager::overlays = overlaysPtr;
        }

        std::stack<std::unique_ptr<Scene::Scene>> *SceneManager::GetScenes() {
            return SceneManager::scenes;
        }

        std::vector<std::unique_ptr<Scene::Scene>> *SceneManager::GetOverlays() {
            return SceneManager::overlays;
        }

        // ---- RESOURCE MANAGER ----

        TextureManager ResourceManager::textureManager;
        FontManager ResourceManager::fontManager;
        SceneManager ResourceManager::sceneManager;

        sf::RenderWindow* ResourceManager::window = nullptr;
        InputManager* ResourceManager::inputManager = nullptr;

        void ResourceManager::LoadTexture(const std::string& name, const std::string& filePath) {
            textureManager.LoadTexture(name, filePath);
        }

        sf::Texture& ResourceManager::GetTexture(const std::string& name) {
            return textureManager.GetTexture(name);
        }

        void ResourceManager::LoadFont(const std::string& name, const std::string& filePath) {
            fontManager.LoadFont(name, filePath);
        }

        sf::Font& ResourceManager::GetFont(const std::string& name) {
            return fontManager.GetFont(name);
        }

        void ResourceManager::SetWindow(sf::RenderWindow* win) {
            window = win;
        }

        sf::RenderWindow* ResourceManager::GetWindow() {
            return window;
        }

        InputManager* ResourceManager::GetInputManager() {
            return inputManager;
        }

        InputManager* ResourceManager::SetInputManager(InputManager* inputMgr) {
            InputManager* oldInputManager = inputManager;
            inputManager = inputMgr;
            return oldInputManager;
        }

    } // namespace ResourceManager
} // namespace Engine
