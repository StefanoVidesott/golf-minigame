#include "settings_scene.hpp"

namespace ApplicationScene {

    void SettingsScene::Start() {
        this->inputManager = Engine::ResourceManager::ResourceManager::GetInputManager();
        this->settingsManager = Engine::ResourceManager::ResourceManager::GetSettingsManager();

        // Create Background Entity
        std::unique_ptr<Engine::Entity> bgPtr = std::make_unique<Engine::Entity>();
        this->bg = bgPtr.get();
        Engine::Components::SpriteComponent *bgSpriteComponent = new Engine::Components::SpriteComponent(Engine::ResourceManager::ResourceManager::GetTextureManager()->GetTexture("background"));
        bgPtr->AddComponent("BackgroundSprite", std::unique_ptr<Engine::Components::Component>(bgSpriteComponent));

        // Create Title Text Entity
        std::unique_ptr<Engine::Entity> titleTextPtr = std::make_unique<Engine::Entity>();
        this->titleText = titleTextPtr.get();
        Engine::Components::TextComponent *titleTextComponent = new Engine::Components::TextComponent("GameFont", "Settings", 54);
        titleTextComponent->SetOrigin(sf::Vector2f(titleTextComponent->GetGlobalBounds().size.x/2, titleTextComponent->GetGlobalBounds().size.y/2));
        titleTextComponent->SetOutlineColor(sf::Color::Black);
        titleTextComponent->SetOutlineThickness(4.f);
        titleTextPtr->AddComponent("TitleText", std::unique_ptr<Engine::Components::Component>(titleTextComponent));

        // Create Back Button Entity
        std::unique_ptr<Engine::Entities::TextButton> backButtonPtr = std::make_unique<Engine::Entities::TextButton>("Back", [this]() { this->OnBackButtonClick(); }, "GameFont", 26);
        this->backButton = backButtonPtr.get();
        backButtonPtr->SetBackgroundTexture(Engine::ResourceManager::ResourceManager::GetTextureManager()->GetTexture("tile64_light"));
        backButtonPtr->SetBackgroundColors({255, 255, 255}, {200, 200 ,200}, {150 ,150 ,150});
        backButtonPtr->SetTextOutlineColor(sf::Color::Black);
        backButtonPtr->SetTextOutlineThickness(2.f);

        // Create Resolution section
        std::unique_ptr<Engine::Entity> resolutionTextPtr = std::make_unique<Engine::Entity>();
        this->resolutionText = resolutionTextPtr.get();
        Engine::Components::TextComponent *resolutionTextComponent = new Engine::Components::TextComponent("GameFont", "Window Resolution:", 28);
        resolutionTextComponent->SetOrigin(sf::Vector2f(0, resolutionTextComponent->GetGlobalBounds().size.y/2));
        resolutionTextComponent->SetOutlineColor(sf::Color::Black);
        resolutionTextComponent->SetOutlineThickness(3.f);
        resolutionTextPtr->AddComponent("Text", std::unique_ptr<Engine::Components::Component>(resolutionTextComponent));

        this->resolutionDropdown = new Engine::Entities::Dropdown(
            {"1600x1200", "1280x960", "960x720", "640x480"},
            this->ActualResolution(),
            "GameFont",
            20,
            sf::Vector2f(20, 15)
        );
        this->resolutionDropdown->SetOnSelectionChanged(
            [this](const std::string& res) { UpdateResolution(res); }
        );
        this->resolutionDropdown->SetButtonTexture(Engine::ResourceManager::ResourceManager::GetTextureManager()->GetTexture("tile64_light"));
        this->resolutionDropdown->SetButtonColors({255, 255, 255}, {200, 200 ,200}, {150 ,150 ,150});
        this->resolutionDropdown->SetTextOutlineColor(sf::Color::Black);
        this->resolutionDropdown->SetTextOutlineThickness(2.f);

        // Create vsync section
        std::unique_ptr<Engine::Entity> vsyncTextPtr = std::make_unique<Engine::Entity>();
        this->vsyncText = vsyncTextPtr.get();
        Engine::Components::TextComponent *vsyncTextComponent = new Engine::Components::TextComponent("GameFont", "Vertical Sync:", 28);
        vsyncTextComponent->SetOrigin(sf::Vector2f(0, vsyncTextComponent->GetGlobalBounds().size.y/2));
        vsyncTextComponent->SetOutlineColor(sf::Color::Black);
        vsyncTextComponent->SetOutlineThickness(3.f);
        vsyncTextPtr->AddComponent("Text", std::unique_ptr<Engine::Components::Component>(vsyncTextComponent));

        std::unique_ptr<Engine::Entities::TextButton> vsyncButtonPtr = std::make_unique<Engine::Entities::TextButton>(ActualVSyncState(), [this]() { this->OnVSyncButtonClick(); }, "GameFont", 30);
        this->vsyncButton = vsyncButtonPtr.get();
        vsyncButtonPtr->SetBackgroundTexture(Engine::ResourceManager::ResourceManager::GetTextureManager()->GetTexture("tile64_light"));
        vsyncButtonPtr->SetBackgroundColors({255, 255, 255}, {200, 200 ,200}, {150 ,150 ,150});
        vsyncButtonPtr->SetTextOutlineColor(sf::Color::Black);
        vsyncButtonPtr->SetTextOutlineThickness(2.f);

        // Create Framelimit section
        std::unique_ptr<Engine::Entity> frameLimitTextPtr = std::make_unique<Engine::Entity>();
        this->frameLimitText = frameLimitTextPtr.get();
        Engine::Components::TextComponent *frameLimitTextComponent = new Engine::Components::TextComponent("GameFont", "FPS Limit:", 28);
        frameLimitTextComponent->SetOrigin(sf::Vector2f(0, frameLimitTextComponent->GetGlobalBounds().size.y/2));
        frameLimitTextComponent->SetOutlineColor(sf::Color::Black);
        frameLimitTextComponent->SetOutlineThickness(3.f);
        frameLimitTextPtr->AddComponent("Text", std::unique_ptr<Engine::Components::Component>(frameLimitTextComponent));

        this->frameLimitDropdown = new Engine::Entities::Dropdown(
            {"60", "144", "240", "Unlimited"},
            this->ActualFrameLimit(),
            "GameFont",
            20,
            sf::Vector2f(20, 15)
        );
        this->frameLimitDropdown->SetOnSelectionChanged(
            [this](const std::string& limit) { OnFrameLimitChanged(limit); }
        );
        this->frameLimitDropdown->SetButtonTexture(Engine::ResourceManager::ResourceManager::GetTextureManager()->GetTexture("tile64_light"));
        this->frameLimitDropdown->SetButtonColors({255, 255, 255}, {200, 200 ,200}, {150 ,150 ,150});
        this->frameLimitDropdown->SetTextOutlineColor(sf::Color::Black);
        this->frameLimitDropdown->SetTextOutlineThickness(2.f);

        // Create Music Volume section
        std::unique_ptr<Engine::Entity> musicVolumeTextPtr = std::make_unique<Engine::Entity>();
        this->musicVolumeText = musicVolumeTextPtr.get();
        Engine::Components::TextComponent *musicVolumeTextComponent = new Engine::Components::TextComponent("GameFont", "Music Volume:", 28);
        musicVolumeTextComponent->SetOrigin(sf::Vector2f(0, musicVolumeTextComponent->GetGlobalBounds().size.y/2));
        musicVolumeTextComponent->SetOutlineColor(sf::Color::Black);
        musicVolumeTextComponent->SetOutlineThickness(3.f);
        musicVolumeTextPtr->AddComponent("Text", std::unique_ptr<Engine::Components::Component>(musicVolumeTextComponent));

        this->musicVolumeSlider = new Engine::Entities::Slider(0.f, 100.f, this->ActualMusicVolume());
        this->musicVolumeSlider->SetSize(sf::Vector2f(200.f, 10.f));
        // this->musicVolumeSlider->SetTrackTexture(Engine::ResourceManager::ResourceManager::GetTextureManager()->GetTexture("tile64_light"));
        this->musicVolumeSlider->SetHandleTexture(Engine::ResourceManager::ResourceManager::GetTextureManager()->GetTexture("tile64_light"));
        this->musicVolumeSlider->SetOnValueChanged(
            [this](float volume) { OnMusicVolumeChanged(volume); }
        );
        this->musicVolumeSlider->SetHandleSize(sf::Vector2f(15.f, 25.f));
        this->musicVolumeSlider->SetColors({85, 120, 70}, {255, 255, 255});

        // Create sfx Volume section
        std::unique_ptr<Engine::Entity> sfxVolumeTextPtr = std::make_unique<Engine::Entity>();
        this->sfxVolumeText = sfxVolumeTextPtr.get();
        Engine::Components::TextComponent *sfxVolumeTextComponent = new Engine::Components::TextComponent("GameFont", "SFX Volume:", 28);
        sfxVolumeTextComponent->SetOrigin(sf::Vector2f(0, sfxVolumeTextComponent->GetGlobalBounds().size.y/2));
        sfxVolumeTextComponent->SetOutlineColor(sf::Color::Black);
        sfxVolumeTextComponent->SetOutlineThickness(3.f);
        sfxVolumeTextPtr->AddComponent("Text", std::unique_ptr<Engine::Components::Component>(sfxVolumeTextComponent));

        this->sfxVolumeSlider = new Engine::Entities::Slider(0.f, 100.f, this->ActualSFXVolume());
        this->sfxVolumeSlider->SetSize(sf::Vector2f(200.f, 10.f));
        // this->sfxVolumeSlider->SetTrackTexture(Engine::ResourceManager::ResourceManager::GetTextureManager()->GetTexture("tile64_light"));
        this->sfxVolumeSlider->SetHandleTexture(Engine::ResourceManager::ResourceManager::GetTextureManager()->GetTexture("tile64_light"));
        this->sfxVolumeSlider->SetOnValueChanged(
            [this](float volume) { OnSFXVolumeChanged(volume); }
        );
        this->sfxVolumeSlider->SetHandleSize(sf::Vector2f(15.f, 25.f));
        this->sfxVolumeSlider->SetColors({85, 120, 70}, {255, 255, 255});

        // Add entities to the scene
        this->entities.push_back(std::move(bgPtr));
        this->entities.push_back(std::move(titleTextPtr));
        this->entities.push_back(std::move(backButtonPtr));
        this->entities.push_back(std::move(resolutionTextPtr));
        this->entities.push_back(std::unique_ptr<Engine::Entity>(this->resolutionDropdown));
        this->entities.push_back(std::move(vsyncTextPtr));
        this->entities.push_back(std::move(vsyncButtonPtr));
        this->entities.push_back(std::move(frameLimitTextPtr));
        this->entities.push_back(std::unique_ptr<Engine::Entity>(this->frameLimitDropdown));
        this->entities.push_back(std::move(musicVolumeTextPtr));
        this->entities.push_back(std::unique_ptr<Engine::Entity>(this->musicVolumeSlider));
        this->entities.push_back(std::move(sfxVolumeTextPtr));
        this->entities.push_back(std::unique_ptr<Engine::Entity>(this->sfxVolumeSlider));

        this->PlaceEntities();
    }

    void SettingsScene::PlaceEntities() {
        sf::Vector2u bgSize = Engine::ResourceManager::ResourceManager::GetTextureManager()->GetTexture("background").getSize();
        sf::Vector2u windowSize = this->window->getSize();
        sf::Vector2f scaleFactor = sf::Vector2f(static_cast<float>(windowSize.x) / bgSize.x, static_cast<float>(windowSize.y) / bgSize.y);

        this->bg->GetTransform()->SetScale(scaleFactor);

        this->titleText->GetTransform()->SetScale(scaleFactor);
        this->titleText->GetTransform()->SetPosition(sf::Vector2f(windowSize.x / 2.f, 50 * scaleFactor.y));

        this->backButton->GetTransform()->SetScale(scaleFactor);
        this->backButton->GetTransform()->SetPosition(sf::Vector2f(75*scaleFactor.x, 60*scaleFactor.y));

        this->resolutionText->GetTransform()->SetScale(scaleFactor);
        this->resolutionText->GetTransform()->SetPosition(sf::Vector2f(75*scaleFactor.x, 140*scaleFactor.y));
        this->resolutionDropdown->SetScale(scaleFactor);
        this->resolutionDropdown->SetPosition(sf::Vector2f(460 * scaleFactor.x, 150 * scaleFactor.y));

        this->vsyncText->GetTransform()->SetScale(scaleFactor);
        this->vsyncText->GetTransform()->SetPosition(sf::Vector2f(75*scaleFactor.x, 200*scaleFactor.y));
        this->vsyncButton->GetTransform()->SetScale(scaleFactor);
        this->vsyncButton->GetTransform()->SetPosition(sf::Vector2f(460 * scaleFactor.x, 210 * scaleFactor.y));

        this->frameLimitText->GetTransform()->SetScale(scaleFactor);
        this->frameLimitText->GetTransform()->SetPosition(sf::Vector2f(75*scaleFactor.x, 260*scaleFactor.y));
        this->frameLimitDropdown->SetScale(scaleFactor);
        this->frameLimitDropdown->SetPosition(sf::Vector2f(460 * scaleFactor.x, 270 * scaleFactor.y));

        this->musicVolumeText->GetTransform()->SetScale(scaleFactor);
        this->musicVolumeText->GetTransform()->SetPosition(sf::Vector2f(75*scaleFactor.x, 320*scaleFactor.y));
        this->musicVolumeSlider->SetScale(scaleFactor);
        this->musicVolumeSlider->SetPosition(sf::Vector2f(360 * scaleFactor.x, 330 * scaleFactor.y));

        this->sfxVolumeText->GetTransform()->SetScale(scaleFactor);
        this->sfxVolumeText->GetTransform()->SetPosition(sf::Vector2f(75*scaleFactor.x, 380*scaleFactor.y));
        this->sfxVolumeSlider->SetScale(scaleFactor);
        this->sfxVolumeSlider->SetPosition(sf::Vector2f(360 * scaleFactor.x, 390 * scaleFactor.y));
    }

    void SettingsScene::UpdateBehavior(float deltaTime) {
    }

    void SettingsScene::HandleEvent(const std::optional<sf::Event>& event) {
        if(this->inputManager) {
            if(this->inputManager->IsKeyPressed(sf::Keyboard::Key::Escape)) {
                Engine::ResourceManager::ResourceManager::GetSceneManager()->DropScene();
            }
        }
    }

    void SettingsScene::RenderBehavior() {
        this->frameLimitDropdown->RenderCustomBehavior(this->window);
        this->resolutionDropdown->RenderCustomBehavior(this->window);
    }

    std::string SettingsScene::GetName() const {
        return "SettingsScene";
    }

    void SettingsScene::UpdateResolution(const std::string& resolution) {
        size_t xpos = resolution.find('x');
        if (xpos == std::string::npos) {
            return;
        }
        int width = std::stoi(resolution.substr(0, xpos));
        int height = std::stoi(resolution.substr(xpos + 1));

        Engine::ResourceManager::SettingsManager* settingsManager = Engine::ResourceManager::ResourceManager::GetSettingsManager();
        settingsManager->Set("window_width", width);
        settingsManager->Set("window_height", height);
        settingsManager->ApplyWindowSize();
        settingsManager->SaveSettings();

        if (this->window) {
            this->window->setSize({static_cast<unsigned int>(width), static_cast<unsigned int>(height)});
            this->PlaceEntities();
        }
    }

    void SettingsScene::OnBackButtonClick() {
        Engine::ResourceManager::ResourceManager::GetSceneManager()->DropScene();
    }

    void SettingsScene::OnVSyncButtonClick() {
        bool vsync = this->settingsManager->Get<bool>("vsync", false);
        vsync = !vsync;
        this->settingsManager->Set("vsync", vsync);
        this->settingsManager->ApplyVideoSettings();
        this->settingsManager->SaveSettings();

        this->vsyncButton->SetTextString(ActualVSyncState());
    }

    void SettingsScene::OnFrameLimitChanged(const std::string& limit) {
        int frameLimit = 0;
        if (limit != "Unlimited") {
            frameLimit = std::stoi(limit);
        }

        this->settingsManager->Set("framerate_limit", frameLimit);
        this->settingsManager->ApplyVideoSettings();
        this->settingsManager->SaveSettings();
    }

    void SettingsScene::OnMusicVolumeChanged(float volume) {
        this->settingsManager->Set("music_volume", volume);
        this->settingsManager->SaveSettings();

        Engine::ResourceManager::ResourceManager::GetAudioManager()->SetMusicVolume(volume);
    }

    void SettingsScene::OnSFXVolumeChanged(float volume) {
        this->settingsManager->Set("sfx_volume", volume);
        this->settingsManager->SaveSettings();

        // Engine::ResourceManager::ResourceManager::GetAudioManager()->SetSFXVolume(volume); // TODO
    }

    std::string SettingsScene::ActualResolution() const {
        int width = this->settingsManager->Get<int>("window_width", 1280);
        int height = this->settingsManager->Get<int>("window_height", 720);
        return (std::to_string(width) + "x" + std::to_string(height));
    }

    std::string SettingsScene::ActualVSyncState() const {
        bool vsync = this->settingsManager->Get<bool>("vsync", false);
        return vsync ? "On" : "Off";
    }

    std::string SettingsScene::ActualFrameLimit() const {
        int limit = this->settingsManager->Get<int>("framerate_limit", 60);
        if (limit == 0) {
            return "Unlimited";
        }
        return std::to_string(limit);
    }

    float SettingsScene::ActualMusicVolume() const {
        return this->settingsManager->Get<float>("music_volume", 50.f);
    }

    float SettingsScene::ActualSFXVolume() const {
        return this->settingsManager->Get<float>("sfx_volume", 50.f);
    }

} // namespace ApplicationScene
