#pragma once

#include "../structs/scatter_info.h"

class Material {
public:
    [[nodiscard]] virtual ScatterInfo scatter(const Ray &ray, const glm::vec3 &pos, const glm::vec3 &normal,
                                              const glm::vec2 &uv, bool frontFace) const = 0;

    [[nodiscard]] virtual glm::vec3 emitted(const glm::vec3 &pos, const glm::vec2 &uv) const {
        return {0.0f, 0.0f, 0.0f};
    }

};
