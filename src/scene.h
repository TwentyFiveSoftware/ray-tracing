#pragma once

#include "camera.h"
#include "objects/hittable_list.h"
#include "objects/bvh_node.h"

class Scene {
public:
    explicit Scene(const HittableList &objects);

    static Scene createRandomScene();

    static Scene createTestScene();

    [[nodiscard]] Camera getCamera() const;

    [[nodiscard]] BVHNode getObjects() const;

private:
    Camera camera;
    BVHNode objects;

};
