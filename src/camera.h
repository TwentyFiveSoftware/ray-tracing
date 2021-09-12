#pragma once

#include "ray.h"
#include "structs/camera_settings.h"

class Camera {
public:
    Camera(CameraSettings cameraSettings);

    [[nodiscard]] Ray getRay(float u, float v) const;

private:
    CameraSettings cameraSettings;
    float viewportHeight;
    float viewportWidth;
    glm::vec3 upperLeftCorner;
    glm::vec3 horizontal;
    glm::vec3 vertical;
    glm::vec3 right;
    glm::vec3 up;

};
