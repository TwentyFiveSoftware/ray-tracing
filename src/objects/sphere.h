#pragma once

#include "hittable.h"

class Sphere : public Hittable {
public:
    Sphere();

    Sphere(glm::vec3 center, float radius);

    bool hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const override;

private:
    glm::vec3 center;
    float radius;

};

