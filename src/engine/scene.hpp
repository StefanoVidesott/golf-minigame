#pragma once

#include "entity.hpp"

#include "entities/text_button.hpp"
#include "entities/dropdown.hpp"

namespace Engine {
    namespace Scene {

        class Scene {
            public:
                Scene() = default;
                virtual ~Scene() = default;

                void Update(float);
                void Render();

                virtual void Start() = 0;
                virtual void UpdateBehavior(float) = 0;
                virtual void HandleEvent(const std::optional<sf::Event>&) = 0;
                virtual void RenderBehavior() = 0;
                virtual void PlaceEntities() {}

                virtual std::string GetName() const = 0;
                virtual void ToggleGizmos();

                void SetWindow(sf::RenderWindow*);
                void SetActive(bool);
                void SetVisible(bool);
                void SetGizmosEnabled(bool);

                bool IsActive() const;
                bool IsVisible() const;
                bool AreGizmosEnabled() const;

                std::vector<std::unique_ptr<Entity>> *GetEntityList();
                int GetEntityCount() const;

            protected:
                sf::RenderWindow *window = nullptr;
                bool active = false;
                bool visible = true;

                bool gizmosEnabled = false;

                std::vector<std::unique_ptr<Entity>> entities;
        };

    } // namespace Scene
} // namespace Engine
