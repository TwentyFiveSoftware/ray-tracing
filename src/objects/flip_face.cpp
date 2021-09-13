#include "flip_face.h"

FlipFace::FlipFace(std::shared_ptr<Hittable> object) :
        object(std::move(object)) {}

bool FlipFace::hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const {
    if (!object->hit(ray, tMin, tMax, record))
        return false;

    record.frontFace = !record.frontFace;
    return true;
}

bool FlipFace::boundingBox(AABB &outputBox) const {
    return object->boundingBox(outputBox);
}

float FlipFace::pdfValue(const glm::vec3 &origin, const glm::vec3 &direction) const {
    return object->pdfValue(origin, direction);
}

glm::vec3 FlipFace::randomPoint(const glm::vec3 &origin) const {
    return object->randomPoint(origin);
}
