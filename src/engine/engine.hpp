#pragma once

#include <SFML/Graphics.hpp>

namespace Engine {

    class Engine {
        public:
            Engine();
            ~Engine();

            void Run();
        private:
            void Update();

            sf::RenderWindow *window;
        };
};
