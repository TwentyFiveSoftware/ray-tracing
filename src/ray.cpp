#include "ray.h"

Ray::Ray() : origin(), direction() {}

Ray::Ray(const glm::vec3 &origin, const glm::vec3 &direction) :
        origin(origin), direction(direction) {}

const glm::vec3* Ray::getOrigin() const {
    return &origin;
}

const glm::vec3* Ray::getDirection() const {
    return &direction;
}

glm::vec3 Ray::at(float t) const {
    return origin + direction * t;
}
