#include "constant_medium.h"
#include <utility>
#include "../material/material_isotropic.h"
#include "../utils/utils.h"
#include "../texture/texture_solid_color.h"

ConstantMedium::ConstantMedium(std::shared_ptr<Hittable> object, float density, const std::shared_ptr<Texture> &texture)
        : object(std::move(object)), density(density), material(std::make_shared<MaterialIsotropic>(texture)) {}


ConstantMedium::ConstantMedium(std::shared_ptr<Hittable> object, float density, const glm::vec3 &color)
        : object(std::move(object)), density(density),
          material(std::make_shared<MaterialIsotropic>(std::make_shared<TextureSolidColor>(color))) {}

bool ConstantMedium::hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const {
    HitRecord record1, record2;

    if (!object->hit(ray, -INFINITY, INFINITY, record1))
        return false;

    if (!object->hit(ray, record1.t + 0.0001f, INFINITY, record2))
        return false;

    record1.t = std::max(record1.t, tMin);
    record2.t = std::min(record2.t, tMax);

    if (record1.t >= record2.t)
        return false;

    const float rayLength = glm::length(ray.getDirection());
    const float distanceInsideObject = (record2.t - record1.t) * rayLength;
    const float hitDistance = (-1.0f / density) * std::log(randomFloat());

    if (hitDistance > distanceInsideObject)
        return false;

    record.t = record1.t + hitDistance / rayLength;
    record.pos = ray.at(record.t);
    record.normal = glm::vec3(1.0f, 0.0f, 0.0f);
    record.frontFace = true;
    record.materialPtr = material;
    return true;
}

bool ConstantMedium::boundingBox(AABB &outputBox) const {
    return object->boundingBox(outputBox);
}
