#include "aabb.h"

AABB::AABB() : minimum(), maximum() {};

AABB::AABB(const glm::vec3 &pointA, const glm::vec3 &pointB) :
        minimum(pointA), maximum(pointB) {}

glm::vec3 AABB::min() const {
    return minimum;
}

glm::vec3 AABB::max() const {
    return maximum;
}

bool AABB::hit(const Ray &ray, float tMin, float tMax) const {
    for (uint8_t axis = 0; axis < 3; axis++) {
        float p1 = (minimum[axis] - ray.getOrigin()[axis]) / ray.getDirection()[axis];
        float p2 = (maximum[axis] - ray.getOrigin()[axis]) / ray.getDirection()[axis];

        float t0 = std::min(p1, p2);
        float t1 = std::max(p1, p2);

        if (std::min(t1, tMax) <= std::max(t0, tMin))
            return false;
    }

    return true;
}