#pragma once

#include "hittable.h"

class RotationY : public Hittable {
public:
    RotationY(const std::shared_ptr<Hittable> &object, float angle);

    bool hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const override;

    bool boundingBox(AABB &outputBox) const override;

private:
    std::shared_ptr<Hittable> object;
    float sinTheta, cosTheta;
    bool hasBox;
    AABB bbox;

};
