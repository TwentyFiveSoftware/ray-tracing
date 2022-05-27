#pragma once

#include <glm/glm.hpp>
#include "hit_record.h"
#include "ray.h"

class Sphere {
public:
    Sphere();

    Sphere(const glm::vec3 &center, float radius);

    [[nodiscard]] HitRecord rayHitsSphere(const Ray &ray, float tMin, float tMax) const;

private:
    glm::vec3 center;
    float radius;
};
