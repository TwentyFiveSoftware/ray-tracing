#pragma once

#include <memory>
#include "hittable.h"
#include "../utils/utils.h"

class Sphere : public Hittable {
public:
    Sphere();

    Sphere(glm::vec3 center, float radius, std::shared_ptr<Material> material);

    bool hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const override;

    bool boundingBox(AABB &outputBox) const override;

    [[nodiscard]] float pdfValue(const glm::vec3 &origin, const glm::vec3 &direction) const override;

    [[nodiscard]] glm::vec3 randomPoint(const glm::vec3 &origin) const override;

private:
    glm::vec3 center;
    float radius;
    std::shared_ptr<Material> materialPtr;

    static glm::vec2 getSphereUV(const glm::vec3 &point);

};
