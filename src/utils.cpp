#include <glm/glm.hpp>
#include "utils.h"

std::random_device rd;
std::mt19937 engine(rd());
std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

float randomFloat() {
    return distribution(engine);
}

glm::vec3 getRandomUnitVector() {
    while (true) {
        auto point = glm::vec3(randomFloat() * 2.0f - 1.0f, randomFloat() * 2.0f - 1.0f, randomFloat() * 2.0f - 1.0f);

        if (glm::dot(point, point) >= 1.0f) {
            continue;
        }

        return glm::normalize(point);
    }
}

bool isNearZero(const glm::vec3 &vector) {
    float epsilon = 1e-8;
    return std::abs(vector.x) < epsilon && std::abs(vector.y) < epsilon && std::abs(vector.z) < epsilon;
}

glm::vec3 reflect(const glm::vec3 &vector, const glm::vec3 &normal) {
    return vector - normal * (2.0f * glm::dot(vector, normal));
}

glm::vec3 refract(const glm::vec3 &vector, const glm::vec3 &normal, float refractionRatio) {
    float cosTheta = std::min(glm::dot(normal, -vector), 1.0f);
    float sinTheta = std::sqrt(1.0f - cosTheta * cosTheta);

    float r0 = (1.0f - refractionRatio) / (1.0f + refractionRatio);
    float reflectance = r0 * r0 + (1.0f - r0 * r0) * std::pow((1.0f - cosTheta), 5.0f);

    if (refractionRatio * sinTheta > 1.0f || refractionRatio > randomFloat()) {
        return reflect(vector, normal);
    }

    glm::vec3 rOutPerpendicular = (vector + normal * cosTheta) * refractionRatio;
    glm::vec3 rOutParallel = normal * -std::sqrt(1.0f - glm::dot(rOutPerpendicular, rOutPerpendicular));
    return rOutPerpendicular + rOutParallel;
}

// https://www.codespeedy.com/hsv-to-rgb-in-cpp/
glm::vec3 getRandomColor() {
    float h = std::floor(randomFloat() * 360.0f);
    float s = 0.75f, v = 0.45f;

    float C = s * v;
    float X = C * (1.0f - std::fabs(std::fmod(h / 60.0f, 2.0f) - 1.0f));
    float m = v - C;

    float r, g, b;

    if (h >= 0 && h < 60) {
        r = C, g = X, b = 0;
    } else if (h >= 60 && h < 120) {
        r = X, g = C, b = 0;
    } else if (h >= 120 && h < 180) {
        r = 0, g = C, b = X;
    } else if (h >= 180 && h < 240) {
        r = 0, g = X, b = C;
    } else if (h >= 240 && h < 300) {
        r = X, g = 0, b = C;
    } else {
        r = C, g = 0, b = X;
    }

    return {r + m, g + m, b + m};
}
