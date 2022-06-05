#pragma once

#include "vec3.h"

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
    vec3 albedo;
    vec3 albedo2;
    float refractionIndex;
};
