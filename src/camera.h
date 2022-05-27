#pragma once

#include "ray.h"

class Camera {
public:
    Camera(const glm::vec3 &lookFrom,
           const glm::vec3 &lookAt,
           float fov,
           float aperture,
           float focusDistance);

    [[nodiscard]] Ray getRay(float u, float v) const;

private:
    glm::vec3 lookFrom;
    glm::vec3 upperLeftCorner;
    glm::vec3 horizontalDirection;
    glm::vec3 verticalDirection;
    glm::vec3 up;
    glm::vec3 right;
    float aperture;
};