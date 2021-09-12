#pragma once

#include "hittable.h"

class RectangleXY : public Hittable {
public:
    RectangleXY();

    RectangleXY(float x0, float x1, float y0, float y1, float z, std::shared_ptr<Material> material);

    bool hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const override;

    bool boundingBox(AABB &outputBox) const override;

private:
    float x0, x1, y0, y1, z;
    std::shared_ptr<Material> materialPtr;

};
