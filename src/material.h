#pragma once

#include <glm/glm.hpp>

enum MaterialType {
    DIFFUSE,
    METAL,
    DIELECTRIC,
};

enum TextureType {
    SOLID,
    CHECKERED,
};

struct Material {
    MaterialType type;
    TextureType textureType;
    glm::vec3 albedo;
    glm::vec3 albedo2;
    float refractionIndex;
};
