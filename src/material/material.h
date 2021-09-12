#pragma once

#include "../structs/scatter_info.h"

class Material {
public:
    [[nodiscard]] virtual ScatterInfo scatter(const Ray &ray, const glm::vec3 &pos, const glm::vec3 &normal,
                                              bool frontFace) const = 0;

};