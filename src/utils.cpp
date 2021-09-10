#include "utils.h"
#include <random>

float randomFloat(float min, float max) {
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(engine);
}

float clamp(float x, float min, float max) {
    return std::min(std::max(x, min), max);
}
