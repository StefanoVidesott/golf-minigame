#pragma once

#include "../engine/engine.hpp"

class Application {
    public:
        Application();
        ~Application();

        void InitializeResources();

        void Run();
    private:
        Engine::Engine* engine;
};
