#include "scene.h"

#include "material/material_diffuse.h"
#include "material/material_metal.h"
#include "material/material_refractive.h"
#include "objects/sphere.h"

Scene::Scene(HittableList objects) :
        camera(Camera()),
        objects(std::move(objects)) {}

Scene Scene::createRandomScene() {
    auto materialGround = std::make_shared<MaterialDiffuse>(glm::vec3(0.55f, 0.7f, 0.15f));
    auto materialLeft = std::make_shared<MaterialRefractive>(1.5f);
    auto materialCenter = std::make_shared<MaterialDiffuse>(glm::vec3(0.1f, 0.2f, 0.5f));
    auto materialRight = std::make_shared<MaterialMetal>(glm::vec3(0.8f, 0.6f, 0.2f), 0.0f);

    HittableList objects;
    objects.add(std::make_shared<Sphere>(glm::vec3(0.0f, -100.5f, 1.0f), 100.0f, materialGround));
    objects.add(std::make_shared<Sphere>(glm::vec3(-1.0f, 0.0f, 1.0f), 0.5f, materialLeft));
    objects.add(std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, 1.0f), 0.5f, materialCenter));
    objects.add(std::make_shared<Sphere>(glm::vec3(1.0f, 0.0f, 1.0f), 0.5f, materialRight));

    return Scene(objects);
}

Camera Scene::getCamera() const {
    return camera;
}

HittableList Scene::getObjects() const {
    return objects;
}
