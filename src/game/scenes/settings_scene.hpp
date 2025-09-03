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
            Engine::Entities::Dropdown* resolutionDropdown;
            Engine::Entity *bg;
            Engine::Entity *resolutionText;
            // Engine::Entities::TextButton* settingsButton;

            void OnPlayButtonClick();
            void OnSettingsButtonClick();
            void UpdateResolution(const std::string&);
            std::string ActualResolution() const;
        };

} // namespace ApplicationScene
