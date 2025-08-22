#include "application.hpp"
#include "scenes/menu_scene.hpp"

Application::Application() {
    this->engine = new Engine::Engine(sf::VideoMode({960u, 720u}), "Gooolf!", sf::Style::Close);
    this->engine->SetWindowPosition(sf::Vector2i(100, 100));
}

Application::~Application() {
    delete this->engine;
}

void Application::Run() {
    this->engine->LoadScene(std::make_unique<ApplicationScene::MenuScene>());
    this->engine->Run();
}
