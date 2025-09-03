#include "application.hpp"
#include "scenes/menu_scene.hpp"

Application::Application() {
    this->engine = new Engine::Engine(sf::VideoMode({960u, 720u}), "Gooolf!", sf::Style::Close, [this]() { this->InitializeResources(); });
    this->engine->SetWindowPosition(sf::Vector2i(100, 100));
}

Application::~Application() {
    delete this->engine;
}

void Application::Run() {
    Engine::ResourceManager::ResourceManager::GetAudioManager()->SetCurrentMusic("BackgroundMusic");
    Engine::ResourceManager::ResourceManager::GetAudioManager()->GetCurrentMusic()->setLooping(true);
    Engine::ResourceManager::ResourceManager::GetAudioManager()->PlayMusic();

    this->engine->LoadScene(std::make_unique<ApplicationScene::MenuScene>());
    this->engine->Run();
}

void Application::InitializeResources() {
        Engine::ResourceManager::ResourceManager::GetFontManager()->LoadFont("GameFont", "res/font/font.ttf");
        Engine::ResourceManager::ResourceManager::GetTextureManager()->LoadTexture("background", "res/gfx/bg.png");
        Engine::ResourceManager::ResourceManager::GetTextureManager()->LoadTexture("tile64_light", "res/gfx/tile64_light.png");

        Engine::ResourceManager::ResourceManager::GetAudioManager()->LoadMusic("BackgroundMusic", "res/music/bg_music.wav");
}