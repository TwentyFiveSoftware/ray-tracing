#pragma once

#include <glm/glm.hpp>

struct Ray {
    glm::vec3 origin;
    glm::vec3 direction;
};

[[nodiscard]] glm::vec3 rayAt(const Ray &ray, float t);
