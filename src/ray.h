#pragma once

#include <glm/glm.hpp>

class Ray {
public:
    Ray();

    Ray(const glm::vec3 &origin, const glm::vec3 &direction);

    [[nodiscard]] glm::vec3 getOrigin() const;

    [[nodiscard]] glm::vec3 getDirection() const;

    [[nodiscard]] glm::vec3 getNormalizedDirection() const;

    [[nodiscard]] glm::vec3 at(float t) const;

private:
    glm::vec3 origin;
    glm::vec3 direction;

};
