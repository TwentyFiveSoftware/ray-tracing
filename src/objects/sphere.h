#pragma once

#include <memory>
#include "hittable.h"

class Sphere : public Hittable {
public:
    Sphere();

    Sphere(glm::vec3 center, float radius, std::shared_ptr<Material> material);

    bool hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const override;

    bool boundingBox(AABB &outputBox) const override;

private:
    glm::vec3 center;
    float radius;
    std::shared_ptr<Material> materialPtr;

};
