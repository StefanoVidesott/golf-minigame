#pragma once

#include "../../engine/scene.hpp"

namespace GameScene {

    class MenuScene : public Engine::Scene::Scene {
        public:
            MenuScene() = default;
            ~MenuScene() override = default;

            void Start() override;
            void Update(float) override;
            void HandleEvent(const std::optional<sf::Event>&) override;
            void Render() override;

        private:
            // sf::RectangleShape rectangle;
        };

} // namespace GameScene
