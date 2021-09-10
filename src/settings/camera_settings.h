#pragma once

#include "settings.h"
#include <glm/glm.hpp>

struct CameraSettings {
    constexpr static const float VIEWPORT_HEIGHT = 2.0f;
    constexpr static const float VIEWPORT_WIDTH = VIEWPORT_HEIGHT * Settings::ASPECT_RATIO;

    constexpr static const float FOCAL_LENGTH = 1.0f;
};
