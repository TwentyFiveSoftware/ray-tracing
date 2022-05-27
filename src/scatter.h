#pragma once

#include <glm/glm.hpp>
#include "ray.h"
#include "hit_record.h"

struct ScatterInfo {
    bool doesScatter;
    glm::vec3 attenuation;
    Ray scatteredRay;
};


[[nodiscard]] ScatterInfo scatter(const Ray &ray, const HitRecord &hitRecord);
