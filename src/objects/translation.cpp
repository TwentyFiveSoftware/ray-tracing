#include "translation.h"

Translation::Translation(std::shared_ptr<Hittable> object, const glm::vec3 &offset) :
        object(std::move(object)), offset(offset) {}

bool Translation::hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const {
    Ray movedRay(ray.getOrigin() - offset, ray.getDirection());

    if (!object->hit(movedRay, tMin, tMax, record))
        return false;

    record.pos += offset;
    record.setFaceNormal(movedRay, record.normal);
    return true;
}

bool Translation::boundingBox(AABB &outputBox) const {
    if (!object->boundingBox(outputBox))
        return false;

    outputBox = AABB(outputBox.min() + offset, outputBox.max() + offset);
    return true;
}

float Translation::pdfValue(const glm::vec3 &origin, const glm::vec3 &direction) const {
    return object->pdfValue(origin - offset, direction);
}

glm::vec3 Translation::randomPoint(const glm::vec3 &origin) const {
    return object->randomPoint(origin - offset);
}
