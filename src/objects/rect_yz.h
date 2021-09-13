#pragma once

#include "hittable.h"

class RectangleYZ : public Hittable {
public:
    RectangleYZ();

    RectangleYZ(float y0, float y1, float z0, float z1, float x, std::shared_ptr<Material> material);

    bool hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const override;

    bool boundingBox(AABB &outputBox) const override;

    [[nodiscard]] float pdfValue(const glm::vec3 &origin, const glm::vec3 &direction) const override;

    [[nodiscard]] glm::vec3 randomPoint(const glm::vec3 &origin) const override;

private:
    float y0, y1, z0, z1, x;
    std::shared_ptr<Material> materialPtr;

};
