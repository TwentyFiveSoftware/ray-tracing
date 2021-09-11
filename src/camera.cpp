#include "camera.h"
#include "settings/camera_settings.h"
#include "settings/settings.h"
#include "utils.h"

Camera::Camera() :
        viewportHeight(std::tan(degreesToRadians(CameraSettings::FOV) / 2.0f) * 2.0f),
        viewportWidth(viewportHeight * Settings::ASPECT_RATIO),
        upperLeftCorner(), horizontal(), vertical() {
    glm::vec3 forward = glm::normalize(CameraSettings::LOOK_AT - CameraSettings::LOOK_FROM);
    glm::vec3 right = glm::normalize(glm::cross(CameraSettings::UP, forward));
    glm::vec3 up = glm::normalize(glm::cross(forward, right));

    horizontal = viewportWidth * right;
    vertical = viewportHeight * up;
    upperLeftCorner = CameraSettings::LOOK_FROM - horizontal / 2.0f + vertical / 2.0f + forward;
}

Ray Camera::getRay(float u, float v) const {
    glm::vec3 direction = upperLeftCorner + horizontal * u - vertical * v - CameraSettings::LOOK_FROM;
    return Ray(CameraSettings::LOOK_FROM, direction);
}
