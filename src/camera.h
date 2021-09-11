#pragma once

#include "ray.h"

class Camera {
public:
    Camera();

    [[nodiscard]] Ray getRay(float u, float v) const;

private:
    float viewportHeight;
    float viewportWidth;
    glm::vec3 upperLeftCorner;
    glm::vec3 horizontal;
    glm::vec3 vertical;
    glm::vec3 right;
    glm::vec3 up;

};
