#include "resource_manager.hpp"

#include "scene.hpp"

namespace Engine {
    namespace ResourceManager {

        std::unordered_map<std::string, std::shared_ptr<std::vector<unsigned char>>> ResourceManager::g_decodedBlobs;

        std::string ResourceManager::NormalizePath(const std::string& path) {
            if (path.rfind("./", 0) == 0) return path.substr(2);
            return path;
        }

        static std::string EncodePath(const std::string& path) {
            return base64::to_base64(path);
        }

        std::shared_ptr<std::vector<unsigned char>> ResourceManager::GetDecodedBlob(const std::string& name) {
            std::string norm = NormalizePath(name);
            auto it = g_decodedBlobs.find(norm);
            if (it != g_decodedBlobs.end()) return it->second;

            const std::string encodedPath = EncodePath(norm);
            const std::string encFilePath = "res/" + encodedPath;

            std::ifstream in(encFilePath);
            if (!in) {
                throw std::runtime_error("Encoded resource file not found: " + encFilePath);
            }

            std::stringstream buffer;
            buffer << in.rdbuf();
            std::string encoded = buffer.str();

            encoded.erase(std::remove_if(encoded.begin(), encoded.end(), ::isspace), encoded.end());

            std::string tmp = base64::from_base64(encoded);
            auto blob = std::make_shared<std::vector<unsigned char>>(tmp.begin(), tmp.end());

            g_decodedBlobs.emplace(norm, blob);

            // std::cout << "Decoded & cached: " << norm << " from " << encFilePath << " (" << blob->size() << " bytes)\n";

            return blob;
        }

        // ---- TEXTURE MANAGER ----

        void TextureManager::LoadTexture(const std::string& name, const std::string& filePath) {
            auto data = ResourceManager::GetDecodedBlob(filePath);
            auto texturePtr = std::make_unique<sf::Texture>();

            if (!texturePtr->loadFromMemory(data->data(), data->size())) {
                throw std::runtime_error("Failed to load texture from encoded file: " + filePath);
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
            auto data = ResourceManager::GetDecodedBlob(filePath);
            auto fontPtr = std::make_unique<sf::Font>();

            if (!fontPtr->openFromMemory(data->data(), data->size())) {
                throw std::runtime_error("Failed to load font from encoded file: " + filePath);
            }
            // opzionale: tieni un riferimento al blob se vuoi essere ultra-sicuro
            // (dipende dalla tua versione di SFML; con openFromMemory meglio tenerlo)
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
            auto data = ResourceManager::GetDecodedBlob(filePath);
            auto soundPtr = std::make_unique<sf::SoundBuffer>();

            if (!soundPtr->loadFromMemory(data->data(), data->size())) {
                throw std::runtime_error("Failed to load sound from encoded file: " + filePath);
            }
            sounds[name] = std::move(soundPtr);
        }


        sf::SoundBuffer& AudioManager::GetSound(const std::string& name) {
            std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>>::iterator it = sounds.find(name);
            if (it != sounds.end()) return *(it->second);

            std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>>::iterator def = sounds.find("DefaultSound"); // TODO load default sound
            if (def != sounds.end()) return *(def->second);

            throw std::runtime_error("Sound not found: " + name + " (and DefaultSound missing)");
        }

        void AudioManager::LoadMusic(const std::string& name, const std::string& filePath) {
            auto data = ResourceManager::GetDecodedBlob(filePath);
            auto musicPtr = std::make_unique<sf::Music>();

            if (!musicPtr->openFromMemory(data->data(), data->size())) {
                throw std::runtime_error("Failed to load music from encoded file: " + filePath);
            }

            // conserva il blob finché la musica è in uso
            musicBlobs[name] = data;
            music[name] = std::move(musicPtr);
        }


        sf::Music& AudioManager::GetMusic(const std::string& name) {
            std::unordered_map<std::string, std::unique_ptr<sf::Music>>::iterator it = music.find(name);
            if (it != music.end()) return *(it->second);

            std::unordered_map<std::string, std::unique_ptr<sf::Music>>::iterator def = music.find("DefaultMusic"); // TODO load default music
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

        // ---- SETTINGS MANAGER ----

        void SettingsManager::LoadSettings() {
            namespace fs = std::filesystem;

            if (!fs::exists(configFilePath)) {
                if (auto parent = fs::path(configFilePath).parent_path(); !parent.empty()) {
                    fs::create_directories(parent);
                }
                settings.clear();
                InitDefaultSettings();
                SaveSettings();
                return;
            }

            std::ifstream file(configFilePath);
            if (!file.is_open()) {
                throw std::runtime_error("Failed to open settings file: " + configFilePath);
            }

            settings.clear();
            InitDefaultSettings();

            std::string line;
            while (std::getline(file, line)) {
                if (line.empty() || line[0] == '#') continue;
                std::istringstream iss(line);
                std::string key, value;
                if (std::getline(iss, key, '=') && std::getline(iss, value)) {
                    settings[key] = value;
                }
            }

            this->ApplySettings();
        }

        void SettingsManager::SaveSettings() const {
            namespace fs = std::filesystem;

            if (auto parent = fs::path(configFilePath).parent_path(); !parent.empty()) {
                fs::create_directories(parent);
            }

            std::string tmpPath = configFilePath + ".tmp";
            {
                std::ofstream file(tmpPath, std::ios::trunc);
                if (!file.is_open()) {
                    throw std::runtime_error("Failed to open settings file for writing: " + tmpPath);
                }

                for (const auto& [key, value] : settings) {
                    file << key << "=" << value << "\n";
                }
            }
            fs::rename(tmpPath, configFilePath);
        }

        void SettingsManager::InitDefaultSettings() {
            this->settings["music_volume"]      = "100";
            this->settings["sfx_volume"]        = "100";
            this->settings["framerate_limit"]   = "0";
            this->settings["vertical_sync"]     = "false";
            this->settings["window_height"]     = "720";
            this->settings["window_width"]      = "960";
        }

        void SettingsManager::ApplySettings() {
            this->ApplyWindowSize();
            this->ApplyVideoSettings();
        }

        void SettingsManager::ApplyVideoSettings() {
            bool verticalSync = Get<bool>("vertical_sync", false);
            int frameLimit = Get<int>("framerate_limit", 0);

            if (ResourceManager::GetWindow()) {
                ResourceManager::GetWindow()->setVerticalSyncEnabled(verticalSync);
                ResourceManager::GetWindow()->setFramerateLimit(frameLimit);
            }
        }

        void SettingsManager::ApplyWindowSize() {
            int width = Get<int>("window_width");
            int height = Get<int>("window_height");

            if (ResourceManager::GetWindow()) {
                ResourceManager::GetWindow()->setSize(sf::Vector2u(width, height));
            }
        }

        // ---- RESOURCE MANAGER ----

        TextureManager *ResourceManager::textureManager;
        FontManager *ResourceManager::fontManager;
        AudioManager *ResourceManager::audioManager;
        SceneManager *ResourceManager::sceneManager;
        SettingsManager *ResourceManager::settingsManager;
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

        void ResourceManager::SetSettingsManager(SettingsManager* settingsMgr) {
            settingsManager = settingsMgr;
        }

        SettingsManager* ResourceManager::GetSettingsManager() {
            return settingsManager;
        }

    } // namespace ResourceManager
} // namespace Engine
