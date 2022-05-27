#include "scene.h"

Scene::Scene() : spheres() {
    auto ground = Sphere(glm::vec3(0.0f, -1000.0f, 1.0f), 1000.0f,
                         {MaterialType::DIFFUSE, glm::vec3(0.95f, 0.95f, 0.95f)});
    auto center = Sphere(glm::vec3(0.0f, 1.0f, 0.0), 1.0f,
                         {MaterialType::DIFFUSE, glm::vec3(0.6f, 0.3f, 0.1f)});

    spheres.push_back(ground);
    spheres.push_back(center);
}

std::vector<Sphere> Scene::getSpheres() const {
    return spheres;
}
