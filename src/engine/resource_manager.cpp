#include "resource_manager.hpp"

namespace Engine {
    namespace ResourceManager {

        // ---- TEXTURE MANAGER ----

        void TextureManager::loadTexture(const std::string& name, const std::string& filePath) {
            std::unique_ptr<sf::Texture> texturePtr(new sf::Texture());

            if (!texturePtr->loadFromFile(filePath)) {
                throw std::runtime_error("Failed to load texture: " + filePath);
            }

            textures[name] = std::move(texturePtr);
        }

        sf::Texture& TextureManager::getTexture(const std::string& name) {
            std::unordered_map<std::string, std::unique_ptr<sf::Texture>>::iterator it = textures.find(name);

            if (it == textures.end()) {
                return this->getTexture("DefaultTexture");
            }

            return *(it->second);
        }

        // ---- FONT MANAGER ----

        void FontManager::loadFont(const std::string& name, const std::string& filePath) {
            std::unique_ptr<sf::Font> fontPtr(new sf::Font());

            if (!fontPtr->openFromFile(filePath)) {
                throw std::runtime_error("Failed to load font: " + filePath);
            }

            fonts[name] = std::move(fontPtr);
        }

        sf::Font& FontManager::getFont(const std::string& name) {
            std::unordered_map<std::string, std::unique_ptr<sf::Font>>::iterator it = fonts.find(name);

            if (it == fonts.end()) {
                return this->getFont("DefaultFont");
            }

            return *(it->second);
        }

        // ---- SCENE MANAGER ----
        std::stack<std::unique_ptr<Scene::Scene>> *SceneManager::scenes;
        std::vector<std::unique_ptr<Scene::Scene>> *SceneManager::overlays;

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

        void ResourceManager::loadTexture(const std::string& name, const std::string& filePath) {
            textureManager.loadTexture(name, filePath);
        }

        sf::Texture& ResourceManager::getTexture(const std::string& name) {
            return textureManager.getTexture(name);
        }

        void ResourceManager::loadFont(const std::string& name, const std::string& filePath) {
            fontManager.loadFont(name, filePath);
        }

        sf::Font& ResourceManager::getFont(const std::string& name) {
            return fontManager.getFont(name);
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
