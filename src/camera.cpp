#include "camera.h"
#include "settings/camera_settings.h"
#include "settings/settings.h"
#include "utils.h"

Camera::Camera() :
        viewportHeight(std::tan(degreesToRadians(CameraSettings::FOV) / 2.0f) * 2.0f),
        viewportWidth(viewportHeight * Settings::ASPECT_RATIO),
        origin(glm::vec3(0.0f, 0.0f, 0.0f)),
        upperLeftCorner(origin - glm::vec3(
                viewportWidth / 2.0f,
                -viewportHeight / 2.0f,
                -CameraSettings::FOCAL_LENGTH)
        ) {}

Ray Camera::getRay(float u, float v) const {
    glm::vec3 direction = upperLeftCorner
                          + glm::vec3(viewportWidth, 0.0f, 0.0f) * u
                          - glm::vec3(0.0f, viewportHeight, 0.0f) * v
                          - origin;

    return {origin, direction};
}
