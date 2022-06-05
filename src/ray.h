#pragma once

#include "vec3.h"

struct Ray {
    vec3 origin;
    vec3 direction;
};

[[nodiscard]] vec3 rayAt(const Ray &ray, float t);
