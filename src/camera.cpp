#include "camera.h"
#include "settings.h"
#include "utils/utils.h"

Camera::Camera(CameraSettings cameraSettings) :
        cameraSettings(cameraSettings),
        viewportHeight(std::tan(degreesToRadians(cameraSettings.fov) / 2.0f) * 2.0f),
        viewportWidth(viewportHeight * Settings::ASPECT_RATIO),
        upperLeftCorner(), horizontal(), vertical(), up(), right() {

    glm::vec3 forward = glm::normalize(cameraSettings.lookAt - cameraSettings.lookFrom);
    right = glm::normalize(glm::cross(cameraSettings.up, forward));
    up = glm::normalize(glm::cross(forward, right));

    horizontal = viewportWidth * right * cameraSettings.focusDistance;
    vertical = viewportHeight * up * cameraSettings.focusDistance;
    upperLeftCorner = cameraSettings.lookFrom - horizontal / 2.0f + vertical / 2.0f
                      + forward * cameraSettings.focusDistance;
}

Ray Camera::getRay(float u, float v) const {
    glm::vec3 random = (cameraSettings.aperture / 2.0f) * getRandomPointInUnitDisk();
    glm::vec3 offset = up * random.x + right * random.y;

    glm::vec3 from = cameraSettings.lookFrom + offset;
    glm::vec3 to = upperLeftCorner + horizontal * u - vertical * v;
    return Ray(from, to - from);
}
