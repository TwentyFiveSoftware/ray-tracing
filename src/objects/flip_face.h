#pragma once

#include "hittable.h"

class FlipFace : public Hittable {
public:
    explicit FlipFace(std::shared_ptr<Hittable> object);

    bool hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const override;

    bool boundingBox(AABB &outputBox) const override;

    [[nodiscard]] float pdfValue(const glm::vec3 &origin, const glm::vec3 &direction) const override;

    [[nodiscard]] glm::vec3 randomPoint(const glm::vec3 &origin) const override;

private:
    std::shared_ptr<Hittable> object;

};
