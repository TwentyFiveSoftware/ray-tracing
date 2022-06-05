#include <cmath>

#include "camera.h"
#include "constants.h"
#include "utils.h"

Camera::Camera(const vec3 &lookFrom, const vec3 &lookAt, float fov, float aperture, float focusDistance)
        : lookFrom(lookFrom), aperture(aperture), upperLeftCorner(), horizontalDirection(), verticalDirection(), up(),
          right() {

    float aspectRatio = float(WIDTH) / float(HEIGHT);

    float viewportHeight = std::tan(fov * float(M_PI / 180.0f) * 0.5f) * 2.0f;
    float viewportWidth = viewportHeight * aspectRatio;

    vec3 forward = (lookAt - lookFrom).normalized();
    right = (vec3{0.0f, 1.0f, 0.0f}).cross(forward).normalized();
    up = forward.cross(right).normalized();

    horizontalDirection = right * viewportWidth * focusDistance;
    verticalDirection = up * viewportHeight * focusDistance;
    upperLeftCorner = lookFrom - horizontalDirection * 0.5f + verticalDirection * 0.5f + forward * focusDistance;
}

Ray Camera::getRay(float u, float v) const {
    vec3 random = getRandomUnitVector() * (aperture * 0.5f);
    vec3 offset = up * random.y + right * random.x;

    vec3 from = lookFrom + offset;
    vec3 to = upperLeftCorner + horizontalDirection * u - verticalDirection * v;
    return {from, (to - from).normalized()};
}
