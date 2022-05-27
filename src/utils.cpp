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
        auto point = glm::vec3(randomFloat(-1.0f, 1.0f), randomFloat(-1.0f, 1.0f), 0.0f);

        if (glm::length(point) >= 1) {
            continue;
        }

        return glm::normalize(point);
    }
}

bool isNearZero(const glm::vec3 &vector) {
    float epsilon = 1e-8;
    return std::abs(vector.x) < epsilon && std::abs(vector.y) < epsilon && std::abs(vector.z) < epsilon;
}
