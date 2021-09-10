#include "camera.h"
#include "settings/camera_settings.h"

Camera::Camera() :
        origin(glm::vec3(0.0f, 0.0f, 0.0f)),
        upperLeftCorner(origin - glm::vec3(
                CameraSettings::VIEWPORT_WIDTH / 2.0f,
                -CameraSettings::VIEWPORT_HEIGHT / 2.0f,
                -CameraSettings::FOCAL_LENGTH)
        ) {}

Ray Camera::getRay(float u, float v) const {
    glm::vec3 direction = upperLeftCorner
                          + glm::vec3(CameraSettings::VIEWPORT_WIDTH, 0.0f, 0.0f) * u
                          - glm::vec3(0.0f, CameraSettings::VIEWPORT_HEIGHT, 0.0f) * v
                          - origin;

    return {origin, direction};
}
