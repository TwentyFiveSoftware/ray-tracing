#include "renderer.h"
#include "ray.h"
#include "camera.h"

// returns the first t where the ray intersects with the sphere; if it doesn't intersect: -1.0f
float rayHitsSphere(const glm::vec3 &sphereCenter, float sphereRadius, const Ray &ray) {
    glm::vec3 co = ray.getOrigin() - sphereCenter;
    float a = glm::dot(ray.getDirection(), ray.getDirection());
    float half_b = glm::dot(co, ray.getDirection());
    float c = glm::dot(co, co) - sphereRadius * sphereRadius;
    float discriminant = half_b * half_b - a * c;

    if (discriminant < 0.0f) {
        return -1.0f;
    }

    return (-half_b - std::sqrt(discriminant)) / a;
}

glm::vec3 calculateRayColor(const Ray &ray) {
    const glm::vec3 SPHERE_CENTER = glm::vec3(0.0f, 0.0f, 1.0f);
    const float SPHERE_RADIUS = 0.5f;

    float t = rayHitsSphere(SPHERE_CENTER, SPHERE_RADIUS, ray);

    if (t > 0.0f) {
        glm::vec3 normal = glm::normalize(ray.at(t) - SPHERE_CENTER);
        return 0.5f * (normal + 1.0f);
    }

    // background: linear interpolation between white and blue based on normalized y coordinate of direction vector
    t = 0.5f * (glm::normalize(ray.getDirection()).y + 1.0f);
    return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
}

void renderThreadEntryPoint(uint16_t startY, uint16_t endY,
                            std::array<Pixel, Settings::WIDTH * Settings::HEIGHT>* pixels) {

    for (uint16_t y = startY; y < endY; y++) {
        for (uint16_t x = 0; x < Settings::WIDTH; x++) {
            float u = float(x) / Settings::WIDTH;
            float v = float(y) / Settings::HEIGHT;

            glm::vec3 direction = Camera::UPPER_LEFT_CORNER
                                  + glm::vec3(Camera::VIEWPORT_WIDTH, 0.0f, 0.0f) * u
                                  - glm::vec3(0.0f, Camera::VIEWPORT_HEIGHT, 0.0f) * v
                                  - Camera::ORIGIN;

            Ray ray(Camera::ORIGIN, direction);
            glm::vec3 pixelColor = calculateRayColor(ray);

            pixels->at(y * Settings::WIDTH + x) = {.pos = {x, y}, .color = pixelColor};
        }
    }
}
