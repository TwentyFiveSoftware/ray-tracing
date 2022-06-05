#pragma once

#include "ray.h"
#include "hit_record.h"

struct ScatterInfo {
    bool doesScatter;
    vec3 attenuation;
    Ray scatteredRay;
};


[[nodiscard]] ScatterInfo scatter(const Ray &ray, const HitRecord &hitRecord);
