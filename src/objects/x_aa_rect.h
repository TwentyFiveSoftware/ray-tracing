#pragma once

#include <memory>
#include "hittable.h"

class XAxisAlignedRectangle : public Hittable {
public:
    XAxisAlignedRectangle();

    XAxisAlignedRectangle(float y0, float y1, float z0, float z1, float x, std::shared_ptr<Material> material);

    bool hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const override;

    bool boundingBox(AABB &outputBox) const override;

private:
    float y0, y1, z0, z1, x;
    std::shared_ptr<Material> materialPtr;

};
