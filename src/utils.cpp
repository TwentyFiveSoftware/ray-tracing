#include <glm/glm.hpp>
#include "utils.h"

float randomFloat(float min, float max) {
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(engine);
}

float randomFloat() {
    return randomFloat(0.0f, 1.0f);
}

glm::vec3 getRandomUnitVector() {
    while (true) {
        auto point = glm::vec3(randomFloat(-1.0f, 1.0f), randomFloat(-1.0f, 1.0f), randomFloat(-1.0f, 1.0f));

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
