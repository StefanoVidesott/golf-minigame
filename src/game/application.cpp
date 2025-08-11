#include "application.hpp"

Application::Application() {
    this->engine = new Engine::Engine();
}

Application::~Application() {
    delete this->engine;
}

void Application::Run() {
    // TODO: Load menu scene
    this->engine->Run();
}