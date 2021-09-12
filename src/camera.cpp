#include "camera.h"
#include "settings/camera_settings.h"
#include "settings/settings.h"
#include "utils/utils.h"

Camera::Camera() :
        viewportHeight(std::tan(degreesToRadians(CameraSettings::FOV) / 2.0f) * 2.0f),
        viewportWidth(viewportHeight * Settings::ASPECT_RATIO),
        upperLeftCorner(), horizontal(), vertical(), up(), right() {

    glm::vec3 forward = glm::normalize(CameraSettings::LOOK_AT - CameraSettings::LOOK_FROM);
    right = glm::normalize(glm::cross(CameraSettings::UP, forward));
    up = glm::normalize(glm::cross(forward, right));

    horizontal = viewportWidth * right * CameraSettings::FOCUS_DISTANCE;
    vertical = viewportHeight * up * CameraSettings::FOCUS_DISTANCE;
    upperLeftCorner = CameraSettings::LOOK_FROM - horizontal / 2.0f + vertical / 2.0f
                      + forward * CameraSettings::FOCUS_DISTANCE;
}

Ray Camera::getRay(float u, float v) const {
    glm::vec3 random = (CameraSettings::APERTURE / 2.0f) * getRandomPointInUnitDisk();
    glm::vec3 offset = up * random.x + right * random.y;

    glm::vec3 from = CameraSettings::LOOK_FROM + offset;
    glm::vec3 to = upperLeftCorner + horizontal * u - vertical * v;
    return Ray(from, to - from);
}
