#include "utils.h"
#include <random>

float randomFloat(float min, float max) {
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(engine);
}

float randomFloat() {
    return randomFloat(0.0f, 1.0f);
}

glm::vec3 randomVector(float min, float max) {
    return {randomFloat(min, max), randomFloat(min, max), randomFloat(min, max)};
}

glm::vec3 getRandomPointInUnitSphere() {
    while (true) {
        glm::vec3 point = randomVector(-1.0f, 1.0f);

        if (glm::length(point) >= 1)
            continue;

        return point;
    }
}

glm::vec3 getRandomUnitVector() {
    return glm::normalize(getRandomPointInUnitSphere());
}

bool isVectorNearZero(const glm::vec3 &vector) {
    const float s = 1e-8;
    return std::fabs(vector.x) < s && std::fabs(vector.y) < s && std::fabs(vector.z) < s;
}

glm::vec3 reflectVector(const glm::vec3 &vector, const glm::vec3 &normal) {
    return vector - 2 * glm::dot(vector, normal) * normal;
}
