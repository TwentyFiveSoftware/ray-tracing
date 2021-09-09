#pragma once

#include "../ray.h"
#include "../structs/hit_record.h"

class Hittable {
public:
    virtual bool hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const = 0;
};
