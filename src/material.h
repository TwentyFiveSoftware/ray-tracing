#pragma once

#include <glm/glm.hpp>

enum MaterialType {
    DIFFUSE,
    METAL
};

struct Material {
    MaterialType type;
    glm::vec3 albedo;
};
