#pragma once

#include "material.h"

struct HitRecord {
    bool hit;
    float t;
    vec3 point;
    vec3 normal;
    bool isFrontFace;
    Material material;
};
