#pragma once

#include <memory>
#include "hittable.h"

class YAxisAlignedRectangle : public Hittable {
public:
    YAxisAlignedRectangle();

    YAxisAlignedRectangle(float x0, float x1, float z0, float z1, float y, std::shared_ptr<Material> material);

    bool hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const override;

    bool boundingBox(AABB &outputBox) const override;

private:
    float x0, x1, z0, z1, y;
    std::shared_ptr<Material> materialPtr;

};
