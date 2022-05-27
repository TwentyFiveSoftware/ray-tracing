#pragma once

#include <glm/glm.hpp>
#include "material.h"

struct HitRecord {
    bool hit;
    float t;
    glm::vec3 point;
    glm::vec3 normal;
    bool isFrontFace;
    Material material;
};
