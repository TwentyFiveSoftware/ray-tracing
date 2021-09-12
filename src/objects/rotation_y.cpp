#include "rotation_y.h"
#include "../utils/utils.h"

RotationY::RotationY(const std::shared_ptr<Hittable> &object, float angle) :
        object(object),
        sinTheta(std::sin(degreesToRadians(-angle))),
        cosTheta(std::cos(degreesToRadians(-angle))),
        hasBox(false),
        bbox() {
    hasBox = object->boundingBox(bbox);

    glm::vec3 min = glm::vec3(INFINITY, INFINITY, INFINITY);
    glm::vec3 max = glm::vec3(-INFINITY, -INFINITY, -INFINITY);

    for (uint8_t i = 0; i < 2; i++)
        for (uint8_t j = 0; j < 2; j++)
            for (uint8_t k = 0; k < 2; k++) {
                float x = float(i) * bbox.max().x + (1.0f - float(i)) * bbox.min().x;
                float y = float(j) * bbox.max().y + (1.0f - float(j)) * bbox.min().y;
                float z = float(k) * bbox.max().z + (1.0f - float(k)) * bbox.min().z;

                glm::vec3 rotatedPoint = glm::vec3(cosTheta * x + sinTheta * z, y, -sinTheta * x + cosTheta * z);

                min = glm::min(rotatedPoint, min);
                max = glm::max(rotatedPoint, max);
            }

    bbox = AABB(min, max);
}

bool RotationY::hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const {
    glm::vec3 origin = glm::vec3(
            cosTheta * ray.getOrigin().x - sinTheta * ray.getOrigin().z,
            ray.getOrigin().y,
            sinTheta * ray.getOrigin().x + cosTheta * ray.getOrigin().z
    );

    glm::vec3 direction = glm::vec3(
            cosTheta * ray.getDirection().x - sinTheta * ray.getDirection().z,
            ray.getDirection().y,
            sinTheta * ray.getDirection().x + cosTheta * ray.getDirection().z
    );

    Ray rotatedRay(origin, direction);

    if (!object->hit(rotatedRay, tMin, tMax, record))
        return false;

    glm::vec3 point = glm::vec3(
            cosTheta * record.pos.x + sinTheta * record.pos.z,
            record.pos.y,
            -sinTheta * record.pos.x + cosTheta * record.pos.z
    );

    glm::vec3 normal = glm::vec3(
            cosTheta * record.normal.x + sinTheta * record.normal.z,
            record.normal.y,
            -sinTheta * record.normal.x + cosTheta * record.normal.z
    );

    record.pos = point;
    record.setFaceNormal(rotatedRay, normal);
    return true;
}

bool RotationY::boundingBox(AABB &outputBox) const {
    outputBox = bbox;
    return hasBox;
}
