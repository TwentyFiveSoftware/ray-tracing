#include "ray.h"

Ray::Ray() : m_origin(), m_direction() {}

Ray::Ray(const glm::vec3 &origin, const glm::vec3 &direction) :
        m_origin(origin), m_direction(direction) {}

glm::vec3 Ray::getOrigin() const {
    return m_origin;
}

glm::vec3 Ray::getDirection() const {
    return m_direction;
}

glm::vec3 Ray::at(float t) const {
    return m_origin + m_direction * t;
}
