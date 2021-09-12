#pragma once

#include <glm/glm.hpp>

class Perlin {
public:
    Perlin();

    ~Perlin();

    [[nodiscard]] float noise(const glm::vec3 &point) const;

    [[nodiscard]] float turbulence(const glm::vec3 &point, uint32_t depth) const;

private:
    static const int32_t POINT_COUNT = 256;
    glm::vec3 * randomVectors;
    uint32_t* permutationsX;
    uint32_t* permutationsY;
    uint32_t* permutationsZ;

    static uint32_t* generatePermutations();

    static void permute(uint32_t* points, uint32_t n);

    static float perlinInterpolation(glm::vec3 c[2][2][2], float u, float v, float w);

};
