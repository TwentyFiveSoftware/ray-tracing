#include "utils.h"
#include <random>

const float PI = 3.1415926535897932385f;

float degreesToRadians(float degrees) {
    return degrees * PI / 180.0f;
}

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

// https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
glm::vec3 refractVector(const glm::vec3 &vector, const glm::vec3 &normal, float refractiveIndexRatio) {
    float cosTheta = glm::dot(-vector, normal);
    glm::vec3 A = refractiveIndexRatio * (vector + cosTheta * normal);
    glm::vec3 B = -normal * std::sqrt(1 - refractiveIndexRatio * refractiveIndexRatio * (1 - cosTheta * cosTheta));
    return A + B;
}

// check for total internal reflection -> no refraction
bool canRefract(const glm::vec3 &vector, const glm::vec3 &normal, float refractiveIndexRatio) {
    float cosTheta = glm::dot(-vector, normal);
    float sinTheta = std::sqrt(1.0f - cosTheta * cosTheta);
    return refractiveIndexRatio * sinTheta <= 1.0f;
}

float reflectanceFactorApproximation(const glm::vec3 &vector, const glm::vec3 &normal, float refractionIndexRatio) {
    float r = std::pow((1.0f - refractionIndexRatio) / (1.0f + refractionIndexRatio), 2.0f);
    return r + (1.0f - r) * std::pow(1.0f - glm::dot(-vector, normal), 5.0f);
}
