#pragma once

#include <glm/glm.hpp>
#include "../ray.h"

struct HitRecord {
    glm::vec3 pos;
    glm::vec3 normal;
    float t;
    bool frontFace;

    inline void setFaceNormal(const Ray &ray, const glm::vec3 &outwardNormal) {
        frontFace = glm::dot(ray.getDirection(), outwardNormal) < 0.0f;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};
