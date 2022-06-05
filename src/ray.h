#pragma once

#include "vec3.h"

struct Ray {
    vec3 origin;
    vec3 direction;

    [[nodiscard]] inline vec3 at(float t) const {
        return origin + direction * t;
    }
};
