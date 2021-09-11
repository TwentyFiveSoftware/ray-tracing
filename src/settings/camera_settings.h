#pragma once

#include <glm/glm.hpp>

struct CameraSettings {
    constexpr static const float FOV = 25.0f;
    constexpr static float APERTURE = 0.1f;
    constexpr static float FOCUS_DISTANCE = 10.0f;

    constexpr static const glm::vec3 LOOK_FROM = glm::vec3(12.0f, 2.0f, -3.0f);
    constexpr static const glm::vec3 LOOK_AT = glm::vec3(0.0f, 0.0f, 0.0f);
    constexpr static const glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);
};
