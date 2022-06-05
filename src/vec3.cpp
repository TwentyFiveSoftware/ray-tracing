#include "vec3.h"
#include <cmath>

vec3 vec3::cross(const vec3 &other) const {
    return {
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x,
    };
}

float vec3::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

vec3 vec3::normalized() const {
    return *this / length();
}

vec3 vec3::sqrt() const {
    return {std::sqrt(x), std::sqrt(y), std::sqrt(z)};
}
