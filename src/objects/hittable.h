#pragma once

#include <memory>
#include "../ray.h"
#include "../structs/hit_record.h"
#include "../aabb.h"

class Hittable {
public:
    virtual bool hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const = 0;

    virtual bool boundingBox(AABB &outputBox) const = 0;

};
