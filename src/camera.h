#pragma once

#include "ray.h"
#include "vec3.h"

class Camera {
public:
    Camera(const vec3 &lookFrom,
           const vec3 &lookAt,
           float fov,
           float aperture,
           float focusDistance);

    [[nodiscard]] Ray getRay(float u, float v) const;

private:
    vec3 lookFrom;
    vec3 upperLeftCorner;
    vec3 horizontalDirection;
    vec3 verticalDirection;
    vec3 up;
    vec3 right;
    float aperture;
};