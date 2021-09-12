#pragma once

#include "hittable.h"
#include "hittable_list.h"

class Box : public Hittable {
public:
    Box();

    Box(const glm::vec3 &point0, const glm::vec3 &point1, const std::shared_ptr<Material>& material);

    bool hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const override;

    bool boundingBox(AABB &outputBox) const override;

private:
    glm::vec3 boxMin;
    glm::vec3 boxMax;
    HittableList sides;

};
