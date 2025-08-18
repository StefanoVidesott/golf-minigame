#include "application.hpp"
#include "scenes/menu_scene.hpp"

Application::Application() {
    this->engine = new Engine::Engine();
}

Application::~Application() {
    delete this->engine;
}

void Application::Run() {
    this->engine->LoadScene(std::make_unique<ApplicationScene::MenuScene>());
    this->engine->Run();
}
