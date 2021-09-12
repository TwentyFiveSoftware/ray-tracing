#pragma once

#include <glm/glm.hpp>

struct CameraSettings {
    float fov, aperture = 0.0f, focusDistance = 1.0f;
    glm::vec3 lookFrom, lookAt;
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
};
