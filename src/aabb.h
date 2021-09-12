#pragma once

#include "ray.h"

class AABB {
public:
    AABB();

    AABB(const glm::vec3 &pointA, const glm::vec3 &pointB);

    [[nodiscard]] glm::vec3 min() const;

    [[nodiscard]] glm::vec3 max() const;

    [[nodiscard]] bool hit(const Ray &ray, float tMin, float tMax) const;

private:
    glm::vec3 minimum;
    glm::vec3 maximum;

};
