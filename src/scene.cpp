#include "scene.h"
#include "material/material_diffuse.h"
#include "material/material_metal.h"
#include "material/material_refractive.h"
#include "objects/sphere.h"
#include "texture/texture_checkered.h"

Scene::Scene(const HittableList &objects) :
        camera(Camera()),
        objects(BVHNode(objects)) {}

Scene Scene::createRandomScene() {
    HittableList objects;

    auto textureGround = std::make_shared<TextureCheckered>(
            1.0f, std::make_shared<TextureSolidColor>(glm::vec3(0.05f, 0.05f, 0.05f)),
            std::make_shared<TextureSolidColor>(glm::vec3(0.95f, 0.95f, 0.95f)));
    objects.add(std::make_shared<Sphere>(glm::vec3(0.0f, -1000.0f, 0.0f), 1000.0f,
                                         std::make_shared<MaterialDiffuse>(textureGround)));

    for (int16_t x = -10; x < 10; x++) {
        for (int16_t z = -10; z < 10; z++) {
            glm::vec3 sphereCenter = glm::vec3(float(x) + 0.9f * randomFloat(), 0.2f, float(z) + 0.9f * randomFloat());

            std::shared_ptr<Material> sphereMaterial;

            float mat = randomFloat();

            if (mat < 0.8) {
                glm::vec3 albedo = randomVector(0.0f, 1.0f) * randomVector(0.0f, 1.0f);
                sphereMaterial = std::make_shared<MaterialDiffuse>(albedo);

            } else if (mat < 0.95) {
                glm::vec3 albedo = randomVector(0.5f, 1.0f);
                float fuzz = randomFloat(0.0f, 0.5f);
                sphereMaterial = std::make_shared<MaterialMetal>(albedo, fuzz);

            } else {
                sphereMaterial = std::make_shared<MaterialRefractive>(1.5f);
            }

            objects.add(std::make_shared<Sphere>(sphereCenter, 0.2f, sphereMaterial));
        }
    }

    auto material1 = std::make_shared<MaterialRefractive>(1.5f);
    objects.add(make_shared<Sphere>(glm::vec3(0.0f, 1.0f, 0.0f), 1.0f, material1));

    auto material2 = std::make_shared<MaterialDiffuse>(glm::vec3(0.4f, 0.2f, 0.1f));
    objects.add(make_shared<Sphere>(glm::vec3(-4.0f, 1.0f, 0.0f), 1.0f, material2));

    auto material3 = std::make_shared<MaterialMetal>(glm::vec3(0.7f, 0.6f, 0.5f), 0.0f);
    objects.add(make_shared<Sphere>(glm::vec3(4.0f, 1.0f, 0.0f), 1.0f, material3));


    return Scene(objects);
}

Scene Scene::createTestScene() {
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

BVHNode Scene::getObjects() const {
    return objects;
}
