#include "utils.h"
#include <random>
#include <cmath>

//std::random_device rd;
//std::mt19937 engine(rd());
//std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
//
//float randomFloat() {
//    return distribution(engine);
//}

uint32_t random_seed = 25;

float randomFloat() {
//    return (float) rand() / (float) RAND_MAX;
    random_seed = (214013 * random_seed + 2531011);
    return (float) ((random_seed >> 16) & 0x7FFF) / 0x7FFF;
}

vec3 getRandomUnitVector() {
    while (true) {
        auto point = vec3{randomFloat() * 2.0f - 1.0f, randomFloat() * 2.0f - 1.0f, randomFloat() * 2.0f - 1.0f};

        if (point.dot(point) >= 1.0f) {
            continue;
        }

        return point.normalized();
    }
}

bool isNearZero(const vec3 &vector) {
    float epsilon = 1e-8;
    return std::abs(vector.x) < epsilon && std::abs(vector.y) < epsilon && std::abs(vector.z) < epsilon;
}

vec3 reflect(const vec3 &vector, const vec3 &normal) {
    return vector - normal * (2.0f * vector.dot(normal));
}

vec3 refract(const vec3 &vector, const vec3 &normal, float refractionRatio) {
    float cosTheta = std::min(normal.dot(-vector), 1.0f);
    float sinTheta = std::sqrt(1.0f - cosTheta * cosTheta);

    float r0 = (1.0f - refractionRatio) / (1.0f + refractionRatio);
    float reflectance = r0 * r0 + (1.0f - r0 * r0) * std::pow((1.0f - cosTheta), 5.0f);

    if (refractionRatio * sinTheta > 1.0f || reflectance > randomFloat()) {
        return reflect(vector, normal);
    }

    vec3 rOutPerpendicular = (vector + normal * cosTheta) * refractionRatio;
    vec3 rOutParallel = normal * -std::sqrt(1.0f - rOutPerpendicular.dot(rOutPerpendicular));
    return rOutPerpendicular + rOutParallel;
}

// https://www.codespeedy.com/hsv-to-rgb-in-cpp/
vec3 getRandomColor() {
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
