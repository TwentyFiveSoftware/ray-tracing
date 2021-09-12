#pragma once

#include "hittable.h"

class Translation : public Hittable {
public:
    Translation(std::shared_ptr<Hittable> object, const glm::vec3 &offset);

    bool hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const override;

    bool boundingBox(AABB &outputBox) const override;

private:
    std::shared_ptr<Hittable> object;
    glm::vec3 offset;

};
