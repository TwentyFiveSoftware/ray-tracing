#pragma once

#include "ray.h"

class Camera {
public:
    Camera();

    [[nodiscard]] Ray getRay(float u, float v) const;

private:
    float viewportHeight;
    float viewportWidth;
    glm::vec3 origin;
    glm::vec3 upperLeftCorner;

};
