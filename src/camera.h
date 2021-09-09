#pragma once

#include "settings.h"
#include <glm/glm.hpp>

struct Camera {
    constexpr static const float VIEWPORT_HEIGHT = 2.0f;
    constexpr static const float VIEWPORT_WIDTH = VIEWPORT_HEIGHT * Settings::ASPECT_RATIO;

    constexpr static const float FOCAL_LENGTH = 1.0f;

    constexpr static const glm::vec3 ORIGIN = glm::vec3(0.0f, 0.0f, 0.0f);
    constexpr static const glm::vec3 UPPER_LEFT_CORNER =
            ORIGIN - glm::vec3(VIEWPORT_WIDTH / 2.0f, -VIEWPORT_HEIGHT / 2.0f, -FOCAL_LENGTH);
};
