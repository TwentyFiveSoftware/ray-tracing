#include "onb.h"

OrthonormalBasis::OrthonormalBasis(const glm::vec3 &n) :
        u(), v(), w() {

    w = glm::normalize(n);

    glm::vec3 otherAxis = std::abs(w.x) > 0.9f ? glm::vec3(0.0f, 1.0f, 0.0f) : glm::vec3(1.0f, 0.0f, 0.0f);
    v = glm::normalize(glm::cross(w, otherAxis));
    u = glm::cross(w, v);
}

glm::vec3 OrthonormalBasis::local(const glm::vec3 &a) const {
    return a.x * u + a.y * v + a.z * w;
}

glm::vec3 OrthonormalBasis::getW() const {
    return w;
}
