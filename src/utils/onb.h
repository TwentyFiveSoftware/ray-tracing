#pragma once

#include <glm/glm.hpp>

class OrthonormalBasis {
public:
    explicit OrthonormalBasis(const glm::vec3 &n);

    [[nodiscard]] glm::vec3 local(const glm::vec3 &a) const;

    [[nodiscard]] glm::vec3 getW() const;

private:
    glm::vec3 u, v, w;

};
