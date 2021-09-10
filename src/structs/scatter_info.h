#pragma once

#include "../ray.h"

struct ScatterInfo {
    bool doesScatter;
    glm::vec3 attenuation;
    Ray scatteredRay;
};
