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
                throw std::runtime_error("Texture not found: " + name);
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
                throw std::runtime_error("Font not found: " + name);
            }

            return *(it->second);
        }

        // ---- RESOURCE MANAGER ----

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

    } // namespace ResourceManager
} // namespace Engine
