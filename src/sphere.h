#pragma once

#include "hit_record.h"
#include "ray.h"
#include "material.h"
#include "vec3.h"

class Sphere {
public:
    Sphere();

    Sphere(const vec3 &center, float radius, const Material &material);

    [[nodiscard]] HitRecord rayHitsSphere(const Ray &ray, float tMin, float tMax) const;

private:
    vec3 center;
    float radius;
    Material material;
};
