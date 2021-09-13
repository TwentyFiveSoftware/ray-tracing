#pragma once

#include <glm/glm.hpp>

class PDF {
public:
    virtual ~PDF() = default;

    [[nodiscard]] virtual float value(const glm::vec3 &direction) const = 0;

    [[nodiscard]] virtual glm::vec3 generate() const = 0;

};
