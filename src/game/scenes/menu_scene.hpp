#pragma once

#include "game_scene.hpp"

namespace ApplicationScene {

    class MenuScene : public Engine::Scene::Scene {
        public:
            MenuScene() = default;
            ~MenuScene() override = default;

            void Start() override;
            void UpdateBehavior(float) override;
            void HandleEvent(const std::optional<sf::Event>&) override;
            void RenderBehavior() override;

            std::string GetName() const override;
        private:
            Engine::InputManager *inputManager;
            Engine::Entities::TextButton* playButton;

            void OnPlayButtonClick();
        };

} // namespace ApplicationScene
