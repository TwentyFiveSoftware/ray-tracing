#include <cmath>

#include "camera.h"
#include "constants.h"
#include "utils.h"

Camera::Camera(const glm::vec3 &lookFrom, const glm::vec3 &lookAt, float fov, float aperture, float focusDistance)
        : lookFrom(lookFrom), aperture(aperture), upperLeftCorner(), horizontalDirection(), verticalDirection(), up(),
          right() {

    float aspectRatio = float(WIDTH) / float(HEIGHT);

    float viewportHeight = std::tan(fov * float(M_PI / 180.0f) * 0.5f) * 2.0f;
    float viewportWidth = viewportHeight * aspectRatio;

    glm::vec3 forward = glm::normalize(lookAt - lookFrom);
    right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), forward));
    up = glm::normalize(glm::cross(forward, right));

    horizontalDirection = right * viewportWidth * focusDistance;
    verticalDirection = up * viewportHeight * focusDistance;
    upperLeftCorner = lookFrom - horizontalDirection * 0.5f + verticalDirection * 0.5f + forward * focusDistance;
}

Ray Camera::getRay(float u, float v) const {
    glm::vec3 random = (aperture * 0.5f) * getRandomUnitVector();
    glm::vec3 offset = up * random.y + right * random.x;

    glm::vec3 from = lookFrom + offset;
    glm::vec3 to = upperLeftCorner + horizontalDirection * u - verticalDirection * v;
    return {from, glm::normalize(to - from)};
}
