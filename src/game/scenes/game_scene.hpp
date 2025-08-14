#pragma once

#include "../../engine/scene.hpp"

namespace ApplicationScene {

    class GameScene : public Engine::Scene::Scene {

        public:
            GameScene();
            ~GameScene() override = default;

            void Start() override;
            void UpdateBehavior(float) override;
            void HandleEvent(const std::optional<sf::Event>&) override;
            void RenderBehavior() override;
        private:

    };

} // namespace ApplicationScene