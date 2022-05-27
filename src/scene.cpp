#include "scene.h"

Scene::Scene() : spheres() {
    // ground
    spheres.push_back(Sphere(glm::vec3(0.0f, -1000.0f, 1.0f), 1000.0f,
                             {MaterialType::DIFFUSE, TextureType::CHECKERED, glm::vec3(0.05f, 0.05f, 0.05f),
                              glm::vec3(0.95f, 0.95f, 0.95f)}));

    // left
    spheres.push_back(Sphere(glm::vec3(-4.0f, 1.0f, 0.0), 1.0f,
                             {MaterialType::DIFFUSE, TextureType::SOLID,glm::vec3(0.6f, 0.3f, 0.1f)}));

    // center
    spheres.push_back(Sphere(glm::vec3(0.0f, 1.0f, 0.0), 1.0f,
                             {.type = MaterialType::DIELECTRIC, .refractionIndex = 1.5f}));

    // right
    spheres.push_back(Sphere(glm::vec3(4.0f, 1.0f, 0.0), 1.0f,
                             {MaterialType::METAL, TextureType::SOLID,glm::vec3(0.7f, 0.6f, 0.5f)}));
}

std::vector<Sphere> Scene::getSpheres() const {
    return spheres;
}
