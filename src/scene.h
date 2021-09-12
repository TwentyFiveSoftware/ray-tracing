#pragma once

#include "camera.h"
#include "objects/hittable_list.h"
#include "objects/bvh_node.h"

class Scene {
public:
    Scene(const HittableList &objects, const Camera &camera, const glm::vec3 &backgroundColor);

    static Scene createRandomScene();

    static Scene createTestScene();

    [[nodiscard]] Camera getCamera() const;

    [[nodiscard]] BVHNode getObjects() const;

    [[nodiscard]] glm::vec3 getBackgroundColor() const;

private:
    BVHNode objects;
    Camera camera;
    glm::vec3 backgroundColor;

};
