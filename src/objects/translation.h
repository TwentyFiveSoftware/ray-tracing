#pragma once

#include "hittable.h"

class Translation : public Hittable {
public:
    Translation(std::shared_ptr<Hittable> object, const glm::vec3 &offset);

    bool hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const override;

    bool boundingBox(AABB &outputBox) const override;

    [[nodiscard]] float pdfValue(const glm::vec3 &origin, const glm::vec3 &direction) const override;

    [[nodiscard]] glm::vec3 randomPoint(const glm::vec3 &origin) const override;

private:
    std::shared_ptr<Hittable> object;
    glm::vec3 offset;

};
