#pragma once

#include "hittable.h"
#include "../texture/texture.h"

class ConstantMedium : public Hittable {
public:
    ConstantMedium(std::shared_ptr<Hittable> object, float density, const std::shared_ptr<Texture> &texture);

    ConstantMedium(std::shared_ptr<Hittable> object, float density, const glm::vec3 &color);

    bool hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const override;

    bool boundingBox(AABB &outputBox) const override;

private:
    std::shared_ptr<Hittable> object;
    std::shared_ptr<Material> material;
    float density;

};
