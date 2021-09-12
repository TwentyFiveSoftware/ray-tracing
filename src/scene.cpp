#include "scene.h"
#include "material/material_diffuse.h"
#include "material/material_metal.h"
#include "material/material_refractive.h"
#include "objects/sphere.h"
#include "objects/rect_yz.h"
#include "objects/rect_xz.h"
#include "objects/rect_xy.h"
#include "texture/texture_checkered.h"
#include "texture/texture_noise.h"
#include "texture/texture_image.h"
#include "material/material_diffuse_light.h"

Scene::Scene(const HittableList &objects, const Camera &camera, const glm::vec3 &backgroundColor) :
        objects(BVHNode(objects)), camera(camera), backgroundColor(backgroundColor) {}

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


    Camera camera(
            {
                    .fov = 25.0f,
                    .aperture = 0.1f,
                    .focusDistance = 10.0f,
                    .lookFrom = glm::vec3(12.0f, 2.0f, -3.0f),
                    .lookAt = glm::vec3(0.0f, 0.0f, 0.0f)
            });

    glm::vec3 backgroundColor = glm::vec3(0.70f, 0.80f, 1.00f);

    return Scene(objects, camera, backgroundColor);
}

Scene Scene::createTestScene() {
    HittableList objects;

    auto textureGround = std::make_shared<TextureCheckered>(
            1.0f, std::make_shared<TextureSolidColor>(glm::vec3(0.05f, 0.05f, 0.05f)),
            std::make_shared<TextureSolidColor>(glm::vec3(0.95f, 0.95f, 0.95f)));
    objects.add(std::make_shared<Sphere>(glm::vec3(0.0f, -1000.0f, 0.0f), 1000.0f,
                                         std::make_shared<MaterialDiffuse>(textureGround)));

    objects.add(make_shared<Sphere>(glm::vec3(0.0f, 2.0f, 0.0f), 2.0f,
                                    std::make_shared<MaterialDiffuse>(std::make_shared<TextureNoise>(4.0f))));

    auto diffuseLight = std::make_shared<MaterialDiffuseLight>(glm::vec3(4.0f, 4.0f, 4.0f));
    objects.add(std::make_shared<RectangleXY>(3.0f, 5.0f, 1.0f, 3.0f, 2.0f, diffuseLight));


    Camera camera(
            {
                    .fov = 20.0f,
                    .lookFrom = glm::vec3(26.0f, 3.0f, -6.0f),
                    .lookAt = glm::vec3(0.0f, 2.0f, 0.0f)
            });

    glm::vec3 backgroundColor = glm::vec3(0.0f, 0.0f, 0.0f);

    return Scene(objects, camera, backgroundColor);
}

Scene Scene::createCornellBoxScene() {
    HittableList objects;

    auto red = std::make_shared<MaterialDiffuse>(glm::vec3(0.65f, 0.05f, 0.05f));
    auto white = std::make_shared<MaterialDiffuse>(glm::vec3(0.73f, 0.73f, 0.73f));
    auto green = std::make_shared<MaterialDiffuse>(glm::vec3(0.12f, 0.45f, 0.15f));
    auto light = std::make_shared<MaterialDiffuseLight>(glm::vec3(15.0f, 15.0f, 15.0f));

    objects.add(std::make_shared<RectangleXY>(0.0f, 550.0f, 0.0f, 550.0f, 550.0f, white));
    objects.add(std::make_shared<RectangleXZ>(0.0f, 550.0f, 0.0f, 550.0f, 0.0f, white));
    objects.add(std::make_shared<RectangleXZ>(0.0f, 550.0f, 0.0f, 550.0f, 550.0f, white));
    objects.add(std::make_shared<RectangleYZ>(0.0f, 550.0f, 0.0f, 550.0f, 0.0f, green));
    objects.add(std::make_shared<RectangleYZ>(0.0f, 550.0f, 0.0f, 550.0f, 550.0f, red));
    objects.add(std::make_shared<RectangleXZ>(210.0f, 340.0f, 225.0f, 330.0f, 549.9f, light));

    Camera camera(
            {
                    .fov = 40.0f,
                    .lookFrom = glm::vec3(275.0f, 275.0f, -800.0f),
                    .lookAt = glm::vec3(275.0f, 275.0f, 0.0f)
            });

    glm::vec3 backgroundColor = glm::vec3(0.0f, 0.0f, 0.0f);

    return Scene(objects, camera, backgroundColor);
}

Camera Scene::getCamera() const {
    return camera;
}

BVHNode Scene::getObjects() const {
    return objects;
}

glm::vec3 Scene::getBackgroundColor() const {
    return backgroundColor;
}
