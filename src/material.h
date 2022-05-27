#pragma once

#include <glm/glm.hpp>

enum MaterialType {
    DIFFUSE,
    METAL,
    DIELECTRIC,
};

struct Material {
    MaterialType type;
    glm::vec3 albedo;
    float refractionIndex;
};
