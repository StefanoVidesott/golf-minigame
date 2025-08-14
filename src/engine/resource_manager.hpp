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

        class ResourceManager {
        public:
            ResourceManager() = default;
            ~ResourceManager() = default;

             static void loadTexture(const std::string&, const std::string&);
            static sf::Texture& getTexture(const std::string&);

            static void loadFont(const std::string&, const std::string&);
            static sf::Font& getFont(const std::string&);

        private:
            static TextureManager textureManager;
            static FontManager fontManager;
        };

    } // namespace ResourceManager
} // namespace Engine
