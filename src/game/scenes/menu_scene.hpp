#pragma once

#include "game_scene.hpp"
#include "settings_scene.hpp"

namespace ApplicationScene {

    class MenuScene : public Engine::Scene::Scene {
        public:
            MenuScene() = default;
            ~MenuScene() override = default;

            void Start() override;
            void UpdateBehavior(float) override;
            void HandleEvent(const std::optional<sf::Event>&) override;
            void RenderBehavior() override;
            void PlaceEntities() override;

            std::string GetName() const override;
        private:
            Engine::Entity *bg;
            Engine::Entity *titleEntity;
            Engine::Entities::TextButton* playButton;
            Engine::Entities::TextButton* settingsButton;

            void OnPlayButtonClick();
            void OnSettingsButtonClick();
        };

} // namespace ApplicationScene
