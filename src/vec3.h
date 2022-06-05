#pragma once

struct vec3 {
    float x;
    float y;
    float z;

    inline vec3 operator-() const {
        return {-x, -y, -z};
    }

    inline vec3 operator+(vec3 other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    inline vec3 operator-(vec3 other) const {
        return {x - other.x, y - other.y, z - other.z};
    }

    inline vec3 operator*(vec3 other) const {
        return {x * other.x, y * other.y, z * other.z};
    }

    inline vec3 operator*(float scalar) const {
        return {x * scalar, y * scalar, z * scalar};
    }

    inline vec3 operator/(float scalar) const {
        return {x / scalar, y / scalar, z / scalar};
    }

    [[nodiscard]] inline float dot(const vec3 &other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    [[nodiscard]] vec3 cross(const vec3 &other) const;

    [[nodiscard]] float length() const;

    [[nodiscard]] vec3 normalized() const;

    [[nodiscard]] vec3 sqrt() const;
};
