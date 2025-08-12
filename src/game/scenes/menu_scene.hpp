#pragma once

#include "../../engine/scene.hpp"

namespace GameScene {

    class MenuScene : public Engine::Scene::Scene {
        public:
            MenuScene() = default;
            ~MenuScene() override = default;

            void Start() override;
            void FixedUpdate(float fixedDeltaTime) override;
            void Update(float deltaTime) override;
            void HandleEvent(const std::optional<sf::Event>& event) override;
            void Render() override;

        private:
            sf::RectangleShape rectangle;
            sf::Font *titleFont;
            sf::Text *titleText;
        };

} // namespace GameScene