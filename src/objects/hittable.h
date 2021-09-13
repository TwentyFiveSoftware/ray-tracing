#pragma once

#include <memory>
#include "../ray.h"
#include "../structs/hit_record.h"
#include "../aabb.h"

class Hittable {
public:
    virtual bool hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const = 0;

    virtual bool boundingBox(AABB &outputBox) const = 0;

    [[nodiscard]] virtual float pdfValue(const glm::vec3 &origin, const glm::vec3 &direction) const {
        return 0.0f;
    }

    [[nodiscard]] virtual glm::vec3 randomPoint(const glm::vec3 &origin) const {
        return glm::vec3(1.0f, 0.0f, 0.0f);
    }

};
