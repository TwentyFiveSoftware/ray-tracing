#pragma once

#include "camera.h"
#include "objects/hittable_list.h"

class Scene {
public:
    Scene(HittableList objects);

    static Scene createRandomScene();

    [[nodiscard]] Camera getCamera() const;

    [[nodiscard]] HittableList getObjects() const;

private:
    Camera camera;
    HittableList objects;


};
