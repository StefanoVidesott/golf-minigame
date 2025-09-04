#pragma once

#include "game_scene.hpp"

namespace ApplicationScene {

    class SettingsScene : public Engine::Scene::Scene {
        public:
            SettingsScene() = default;
            ~SettingsScene() override = default;

            void Start() override;
            void UpdateBehavior(float) override;
            void HandleEvent(const std::optional<sf::Event>&) override;
            void RenderBehavior() override;
            void PlaceEntities() override;

            std::string GetName() const override;
        private:
            Engine::InputManager* inputManager;
            Engine::ResourceManager::SettingsManager* settingsManager;

            Engine::Entity *bg;
            Engine::Entity *resolutionText;
            Engine::Entities::Dropdown* resolutionDropdown;
            Engine::Entity *vsyncText;
            Engine::Entities::TextButton* vsyncButton;
            Engine::Entity *frameLimitText;
            Engine::Entities::Dropdown* frameLimitDropdown;
            Engine::Entity *musicVolumeText;
            Engine::Entities::Slider* musicVolumeSlider;
            Engine::Entity *sfxVolumeText;
            Engine::Entities::Slider* sfxVolumeSlider;

            // Engine::Entities::TextButton* backButton;

            void UpdateResolution(const std::string&);
            void OnVSyncButtonClick();
            void OnFrameLimitChanged(const std::string&);
            void OnMusicVolumeChanged(float);
            void OnSFXVolumeChanged(float);

            std::string ActualResolution() const;
            std::string ActualVSyncState() const;
            std::string ActualFrameLimit() const;
            float ActualMusicVolume() const;
            float ActualSFXVolume() const;
        };

} // namespace ApplicationScene
