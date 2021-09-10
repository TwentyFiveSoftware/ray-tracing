#pragma once

#include "ray.h"

class Camera {
public:
    Camera();

    [[nodiscard]] Ray getRay(float u, float v) const;

private:
    glm::vec3 origin;
    glm::vec3 upperLeftCorner;

};
