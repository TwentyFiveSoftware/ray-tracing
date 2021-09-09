#pragma once

#include "settings.h"
#include <glm/glm.hpp>

struct Camera {
    static const uint16_t VIEWPORT_HEIGHT = 2;
    static const uint16_t VIEWPORT_WIDTH = static_cast<uint16_t>(VIEWPORT_HEIGHT * Settings::ASPECT_RATIO);

    constexpr static const float FOCAL_LENGTH = 1.0f;

    constexpr static const glm::vec3 ORIGIN = glm::vec3(0.0f, 0.0f, 0.0f);
    constexpr static const glm::vec3 UPPER_LEFT_CORNER =
            ORIGIN - glm::vec3(VIEWPORT_WIDTH / 2.0f, -VIEWPORT_HEIGHT / 2.0f, -FOCAL_LENGTH);
};
