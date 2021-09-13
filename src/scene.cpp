#include "scene.h"
#include <utility>
#include "material/material_diffuse.h"
#include "material/material_metal.h"
#include "material/material_refractive.h"
#include "objects/sphere.h"
#include "objects/rect_yz.h"
#include "objects/rect_xz.h"
#include "objects/rect_xy.h"
#include "objects/box.h"
#include "texture/texture_checkered.h"
#include "texture/texture_noise.h"
#include "texture/texture_image.h"
#include "material/material_diffuse_light.h"
#include "objects/translation.h"
#include "objects/rotation_y.h"
#include "objects/constant_medium.h"
#include "objects/flip_face.h"

Scene::Scene(const HittableList &objects, std::shared_ptr<HittableList> lights, const Camera &camera,
             const glm::vec3 &backgroundColor) :
        objects(BVHNode(objects)), lights(std::move(lights)), camera(camera), backgroundColor(backgroundColor) {}

Camera Scene::getCamera() const {
    return camera;
}

BVHNode Scene::getObjects() const {
    return objects;
}

glm::vec3 Scene::getBackgroundColor() const {
    return backgroundColor;
}

std::shared_ptr<HittableList> Scene::getLights() const {
    return lights;
}

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

    return Scene(objects, nullptr, camera, backgroundColor);
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
    auto light = std::make_shared<FlipFace>(std::make_shared<RectangleXY>(3.0f, 5.0f, 1.0f, 3.0f, 2.0f, diffuseLight));
    objects.add(light);

    auto lights = std::make_shared<HittableList>();
    lights->add(light);

    Camera camera(
            {
                    .fov = 20.0f,
                    .lookFrom = glm::vec3(26.0f, 3.0f, -6.0f),
                    .lookAt = glm::vec3(0.0f, 2.0f, 0.0f)
            });

    glm::vec3 backgroundColor = glm::vec3(0.0f, 0.0f, 0.0f);

    return Scene(objects, lights, camera, backgroundColor);
}

Scene Scene::createCornellBoxScene() {
    HittableList objects;

    auto red = std::make_shared<MaterialDiffuse>(glm::vec3(0.65f, 0.05f, 0.05f));
    auto white = std::make_shared<MaterialDiffuse>(glm::vec3(0.73f, 0.73f, 0.73f));
    auto green = std::make_shared<MaterialDiffuse>(glm::vec3(0.12f, 0.45f, 0.15f));
    auto lightMat = std::make_shared<MaterialDiffuseLight>(glm::vec3(15.0f, 15.0f, 15.0f));

    objects.add(std::make_shared<RectangleXY>(0.0f, 550.0f, 0.0f, 550.0f, 550.0f, white));
    objects.add(std::make_shared<RectangleXZ>(0.0f, 550.0f, 0.0f, 550.0f, 0.0f, white));
    objects.add(std::make_shared<RectangleXZ>(0.0f, 550.0f, 0.0f, 550.0f, 550.0f, white));
    objects.add(std::make_shared<RectangleYZ>(0.0f, 550.0f, 0.0f, 550.0f, 0.0f, green));
    objects.add(std::make_shared<RectangleYZ>(0.0f, 550.0f, 0.0f, 550.0f, 550.0f, red));

    auto light = std::make_shared<FlipFace>(std::make_shared<RectangleXZ>(
            210.0f, 340.0f, 220.0f, 330.0f, 549.9f, lightMat));
    objects.add(light);


    std::shared_ptr<Hittable> box1 = std::make_shared<Box>(
            glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(165.0f, 165.0f, 165.0f), white);
    box1 = std::make_shared<RotationY>(box1, -18.0f);
    box1 = std::make_shared<Translation>(box1, glm::vec3(265.0f, 0.0f, 130.0f));
    objects.add(box1);


//    std::shared_ptr<Material> glass = std::make_shared<MaterialRefractive>(1.5f);
//    std::shared_ptr<Hittable> sphere = std::make_shared<Sphere>(glm::vec3(350.0f, 90.0f, 190.0f), 90.0f, glass);
//    objects.add(sphere);


//    std::shared_ptr<Material> aluminum = std::make_shared<MaterialMetal>(glm::vec3(0.8f, 0.85f, 0.88f), 0.0f);

    std::shared_ptr<Hittable> box2 = std::make_shared<Box>(
            glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(165.0f, 330.0f, 165.0f), white);
    box2 = std::make_shared<RotationY>(box2, 15.0f);
    box2 = std::make_shared<Translation>(box2, glm::vec3(130.0f, 0.0f, 295.0f));
    objects.add(box2);

    auto lights = std::make_shared<HittableList>();
    lights->add(light);

    Camera camera(
            {
                    .fov = 40.0f,
                    .lookFrom = glm::vec3(275.0f, 275.0f, -800.0f),
                    .lookAt = glm::vec3(275.0f, 275.0f, 0.0f)
            });

    glm::vec3 backgroundColor = glm::vec3(0.0f, 0.0f, 0.0f);

    return Scene(objects, lights, camera, backgroundColor);
}


Scene Scene::createComplexScene() {
    HittableList objects;

    // GROUND
    HittableList boxes;
    const auto materialGround = std::make_shared<MaterialDiffuse>(glm::vec3(0.48f, 0.83f, 0.53f));

    const uint16_t boxesPerSide = 20;
    const float boxSize = 100.0f;

    for (uint16_t i = 0; i < boxesPerSide; i++) {
        for (uint16_t j = 0; j < boxesPerSide; j++) {
            const float x = -1000.0f + float(i) * boxSize;
            const float z = -1000.0f + float(j) * boxSize;

            boxes.add(std::make_shared<Box>(
                    glm::vec3(x, 0.0f, z),
                    glm::vec3(x + boxSize, randomFloat(1.0f, 101.0f), z + boxSize),
                    materialGround
            ));
        }
    }

    objects.add(std::make_shared<BVHNode>(boxes));

    // LIGHT
    const auto lightMaterial = std::make_shared<MaterialDiffuseLight>(glm::vec3(7.0f, 7.0f, 7.0f));
    const auto light = std::make_shared<RectangleXZ>(123.0f, 423.0f, 147.0f, 412.0f, 554.0f, lightMaterial);
    objects.add(light);

    // DIFFUSE SPHERE
    const auto diffuseMaterial = std::make_shared<MaterialDiffuse>(glm::vec3(0.7f, 0.3f, 0.1f));
    objects.add(std::make_shared<Sphere>(glm::vec3(400.0f, 400.0f, 200.0f), 50.0f, diffuseMaterial));

    // REFRACTIVE SPHERE
    const auto refractiveMaterial = std::make_shared<MaterialRefractive>(1.5f);
    objects.add(std::make_shared<Sphere>(glm::vec3(260.0f, 150.0f, 45.0f), 50.0f, refractiveMaterial));

    // FUZZY METAL SPHERE
    const auto fuzzyMetalMaterial = std::make_shared<MaterialMetal>(glm::vec3(0.8f, 0.8f, 0.9f), 1.0f);
    objects.add(std::make_shared<Sphere>(glm::vec3(0.0f, 150.0f, 145.0f), 50.0f, fuzzyMetalMaterial));

    // SUBSURFACE REFLECTION SPHERE
    const auto ssrSphere = std::make_shared<Sphere>(glm::vec3(360.0f, 150.0f, 145.0f), 70.0f, refractiveMaterial);
    objects.add(ssrSphere);
    objects.add(std::make_shared<ConstantMedium>(ssrSphere, 0.2f, glm::vec3(0.2f, 0.4f, 0.9f)));

//    // SCENE FOG
//    const auto fogSphere = std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, 0.0f), 500.0f, refractiveMaterial);
//    objects.add(std::make_shared<ConstantMedium>(fogSphere, 0.1f, glm::vec3(1.0f, 1.0f, 1.0f)));

    // TEXTURE SPHERE
    const auto textureMaterial = std::make_shared<MaterialDiffuse>(std::make_shared<TextureImage>("earthmap.jpg"));
    objects.add(std::make_shared<Sphere>(glm::vec3(400.0f, 200.0f, 400.0f), 100.0f, textureMaterial));

    // NOISE TEXTURED SPHERE
    const auto noiseMaterial = std::make_shared<MaterialDiffuse>(std::make_shared<TextureNoise>(0.1f));
    objects.add(std::make_shared<Sphere>(glm::vec3(220.0f, 280.0f, 300.0f), 80.0f, noiseMaterial));

    // SPHERE COLLECTION
    HittableList sphereCollection;

    const uint16_t sphereAmount = 250;
    const auto whiteMaterial = std::make_shared<MaterialDiffuse>(glm::vec3(0.73f, 0.73f, 0.73f));

    for (uint16_t i = 0; i < sphereAmount; i++) {
        sphereCollection.add(std::make_shared<Sphere>(getRandomUnitVector() * 100.0f, 10.0f, whiteMaterial));
    }

    objects.add(std::make_shared<Translation>(
            std::make_shared<RotationY>(
                    std::make_shared<BVHNode>(sphereCollection), 15.0f
            ),
            glm::vec3(-100.0f, 270.0f, 395.0f)
    ));

    auto lights = std::make_shared<HittableList>();
    lights->add(light);

    //
    Camera camera(
            {
                    .fov = 40.0f,
                    .lookFrom = glm::vec3(478.0f, 278.0f, -600.0f),
                    .lookAt = glm::vec3(278.0f, 278.0f, 0.0f)
            });

    glm::vec3 backgroundColor = glm::vec3(0.0f, 0.0f, 0.0f);

    return Scene(objects, lights, camera, backgroundColor);
}
