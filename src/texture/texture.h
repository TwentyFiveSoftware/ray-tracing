#pragma once

#include <glm/glm.hpp>

class Texture {
public:
    [[nodiscard]] virtual glm::vec3 value(const glm::vec2 &uv, const glm::vec3 &point) const = 0;

};
