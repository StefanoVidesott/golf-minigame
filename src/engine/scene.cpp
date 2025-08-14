#include "scene.hpp"

namespace Engine {
    namespace Scene {

        Scene::~Scene() {
            entities.clear();
        }

    } // namespace Scene
} // namespace Engine