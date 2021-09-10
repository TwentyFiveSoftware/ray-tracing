#pragma once

#include <glm/glm.hpp>
#include "../ray.h"
#include "../material/material.h"

struct HitRecord {
    glm::vec3 pos;
    glm::vec3 normal;
    std::shared_ptr<Material> materialPtr;
    float t;
    bool frontFace;

    inline void setFaceNormal(const Ray &ray, const glm::vec3 &outwardNormal) {
        frontFace = glm::dot(ray.getDirection(), outwardNormal) < 0.0f;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};
