#include "utils.h"
#include <random>

float degreesToRadians(float degrees) {
    return degrees * PI / 180.0f;
}

float randomFloat(float min, float max) {
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_real_distribution<float> distribution(min, max - 0.000001f);
    return distribution(engine);
}

float randomFloat() {
    return randomFloat(0.0f, 1.0f);
}

int32_t randomInt(int32_t min, int32_t max) {
    return static_cast<int32_t>(randomFloat(float(min), float(max + 1)));
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

glm::vec3 getRandomPointInUnitDisk() {
    while (true) {
        glm::vec3 point = glm::vec3(
                randomFloat(-1.0f, 1.0f),
                randomFloat(-1.0f, 1.0f),
                0.0f
        );

        if (glm::length(point) >= 1)
            continue;

        return point;
    }
}

AABB calculateSurroundingBox(AABB box1, AABB box2) {
    glm::vec3 minPoint = glm::min(box1.min(), box2.min());
    glm::vec3 maxPoint = glm::max(box1.max(), box2.max());
    return AABB(minPoint, maxPoint);
}

glm::vec3 randomToSphere(float radius, float distance) {
    float r1 = randomFloat();
    float r2 = randomFloat();

    float phi = 2.0f * PI * r1;
    float z = 1.0f + r2 * (std::sqrt(1.0f - radius * radius / (distance * distance)) - 1.0f);
    float x = std::cos(phi) * std::sqrt(1.0f - z * z);
    float y = std::sin(phi) * std::sqrt(1.0f - z * z);

    return glm::vec3(x, y, z);
}