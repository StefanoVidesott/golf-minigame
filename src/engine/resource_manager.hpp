#pragma once

#include <stack>
#include <memory>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <SFML/Graphics.hpp>

namespace Engine {
    namespace ResourceManager {

        class TextureManager {
        public:
            TextureManager() = default;
            ~TextureManager() = default;

            void loadTexture(const std::string& name, const std::string& filePath);
            sf::Texture& getTexture(const std::string& name);

        private:
            std::unordered_map<std::string, std::unique_ptr<sf::Texture>> textures;
        };

        class FontManager {
        public:
            FontManager() = default;
            ~FontManager() = default;

            void loadFont(const std::string& name, const std::string& filePath);
            sf::Font& getFont(const std::string& name);

        private:
            std::unordered_map<std::string, std::unique_ptr<sf::Font>> fonts;
        };

        class ResourceManager {
        public:
            ResourceManager() = default;
            ~ResourceManager() = default;

            static void loadTexture(const std::string& name, const std::string& filePath);
            static sf::Texture& getTexture(const std::string& name);

            static void loadFont(const std::string& name, const std::string& filePath);
            static sf::Font& getFont(const std::string& name);

        private:
            static TextureManager textureManager;
            static FontManager fontManager;
        };

    } // namespace ResourceManager
} // namespace Engine
