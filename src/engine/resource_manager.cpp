#include "resource_manager.hpp"

#include "scene.hpp"

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

        // ---- AUDIO MANAGER ----

        void AudioManager::LoadSound(const std::string& name, const std::string& filePath) {
            std::unique_ptr<sf::SoundBuffer> soundPtr(new sf::SoundBuffer());

            if (!soundPtr->loadFromFile(filePath)) {
                throw std::runtime_error("Failed to load sound: " + filePath);
            }

            sounds[name] = std::move(soundPtr);
        }

        sf::SoundBuffer& AudioManager::GetSound(const std::string& name) {
            std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>>::iterator it = sounds.find(name);
            if (it != sounds.end()) return *(it->second);

            std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>>::iterator def = sounds.find("DefaultSound"); // TODO
            if (def != sounds.end()) return *(def->second);

            throw std::runtime_error("Sound not found: " + name + " (and DefaultSound missing)");
        }

        void AudioManager::LoadMusic(const std::string& name, const std::string& filePath) {
            std::unique_ptr<sf::Music> musicPtr(new sf::Music());

            if (!musicPtr->openFromFile(filePath)) {
                throw std::runtime_error("Failed to load music: " + filePath);
            }

            music[name] = std::move(musicPtr);
        }

        sf::Music& AudioManager::GetMusic(const std::string& name) {
            std::unordered_map<std::string, std::unique_ptr<sf::Music>>::iterator it = music.find(name);
            if (it != music.end()) return *(it->second);

            std::unordered_map<std::string, std::unique_ptr<sf::Music>>::iterator def = music.find("DefaultMusic");
            if (def != music.end()) return *(def->second);

            throw std::runtime_error("Music not found: " + name + " (and DefaultMusic missing)");
        }

        sf::Music* AudioManager::GetCurrentMusic() {
            return currentMusic;
        }

        void AudioManager::SetCurrentMusic(const std::string& name) {
            sf::Music* musicPtr = &GetMusic(name);
            if (musicPtr) {
                currentMusic = musicPtr;
            }
        }

        void AudioManager::PlayMusic() {
            if (currentMusic) {
                currentMusic->play();
            }
        }

        void AudioManager::PauseMusic() {
            if (currentMusic) {
                currentMusic->pause();
            }
        }

        void AudioManager::StopMusic() {
            if (currentMusic) {
                currentMusic->stop();
            }
        }

        // ---- SCENE MANAGER ----
        void SceneManager::Initialize(std::stack<std::unique_ptr<Scene::Scene>>* scenesPtr,
        std::vector<std::unique_ptr<Scene::Scene>>* overlaysPtr,
        std::function<void(std::unique_ptr<Scene::Scene>)> loadFunc,
        std::function<void()> dropFunc) {
            this->scenes = scenesPtr;
            this->overlays = overlaysPtr;
            this->LoadSceneFunction = std::move(loadFunc);
            this->DropSceneFunction = std::move(dropFunc);
        }

        std::stack<std::unique_ptr<Scene::Scene>> *SceneManager::GetScenes() {
            return this->scenes;
        }

        std::vector<std::unique_ptr<Scene::Scene>> *SceneManager::GetOverlays() {
            return this->overlays;
        }

        void SceneManager::LoadScene(std::unique_ptr<Scene::Scene> scene) {
            if (LoadSceneFunction) LoadSceneFunction(std::move(scene));
        }

        void SceneManager::DropScene() {
            if (DropSceneFunction) DropSceneFunction();
        }

        // ---- RESOURCE MANAGER ----

        TextureManager *ResourceManager::textureManager;
        FontManager *ResourceManager::fontManager;
        AudioManager *ResourceManager::audioManager;
        SceneManager *ResourceManager::sceneManager;
        InputManager *ResourceManager::inputManager;

        sf::RenderWindow *ResourceManager::window = nullptr;

        void ResourceManager::SetWindow(sf::RenderWindow* win) {
            window = win;
        }

        sf::RenderWindow* ResourceManager::GetWindow() {
            return window;
        }

        void ResourceManager::SetTextureManager(TextureManager* texMgr) {
            textureManager = texMgr;
        }

        TextureManager* ResourceManager::GetTextureManager() {
            return textureManager;
        }

        void ResourceManager::SetFontManager(FontManager* fontMgr) {
            fontManager = fontMgr;
        }

        FontManager* ResourceManager::GetFontManager() {
            return fontManager;
        }

        void ResourceManager::SetAudioManager(AudioManager* audioMgr) {
            audioManager = audioMgr;
        }

        AudioManager* ResourceManager::GetAudioManager() {
            return audioManager;
        }

        void ResourceManager::SetSceneManager(SceneManager* sceneMgr) {
            sceneManager = sceneMgr;
        }

        SceneManager* ResourceManager::GetSceneManager() {
            return sceneManager;
        }

        void ResourceManager::SetInputManager(InputManager* inputMgr) {
            inputManager = inputMgr;
        }

        InputManager* ResourceManager::GetInputManager() {
            return inputManager;
        }

    } // namespace ResourceManager
} // namespace Engine
