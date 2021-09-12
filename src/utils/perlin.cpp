#include "perlin.h"
#include "utils.h"

Perlin::Perlin() {
    randomVectors = new glm::vec3[POINT_COUNT];
    for (int32_t i = 0; i < POINT_COUNT; i++) {
        randomVectors[i] = getRandomUnitVector();
    }

    permutationsX = generatePermutations();
    permutationsY = generatePermutations();
    permutationsZ = generatePermutations();
}

Perlin::~Perlin() {
    delete[] randomVectors;
    delete[] permutationsX;
    delete[] permutationsY;
    delete[] permutationsZ;
}

float Perlin::noise(const glm::vec3 &point) const {
    glm::vec3 uvw = point - glm::floor(point);
    glm::ivec3 ijk = glm::floor(point);

    glm::vec3 c[2][2][2];

    for (uint8_t di = 0; di < 2; di++)
        for (uint8_t dj = 0; dj < 2; dj++)
            for (uint8_t dk = 0; dk < 2; dk++)
                c[di][dj][dk] = randomVectors[
                        permutationsX[(ijk.x + di) & 0xFF] ^
                        permutationsY[(ijk.y + dj) & 0xFF] ^
                        permutationsZ[(ijk.z + dk) & 0xFF]
                ];

    return perlinInterpolation(c, uvw.x, uvw.y, uvw.z);
}

float Perlin::turbulence(const glm::vec3 &point, uint32_t depth) const {
    float sum = 0.0f;
    float weight = 1.0f;
    glm::vec3 tempPoint = point;

    for (uint32_t i = 0; i < depth; i++) {
        sum += weight * noise(tempPoint);
        weight *= 0.5f;
        tempPoint *= 2.0f;
    }

    return std::abs(sum);
}

uint32_t* Perlin::generatePermutations() {
    auto points = new uint32_t[POINT_COUNT];

    for (uint32_t i = 0; i < POINT_COUNT; i++) {
        points[i] = i;
    }

    permute(points, POINT_COUNT);
    return points;
}

void Perlin::permute(uint32_t* points, uint32_t n) {
    for (uint32_t i = n - 1; i > 0; i--) {
        uint32_t target = randomInt(0, i);
        uint32_t tmp = points[i];
        points[i] = points[target];
        points[target] = tmp;
    }
}

float Perlin::perlinInterpolation(glm::vec3 c[2][2][2], float u, float v, float w) {
    auto uu = u * u * (3.0f - 2.0f * u);
    auto vv = v * v * (3.0f - 2.0f * v);
    auto ww = w * w * (3.0f - 2.0f * w);

    float sum = 0.0f;

    for (uint8_t i = 0; i < 2; i++)
        for (uint8_t j = 0; j < 2; j++)
            for (uint8_t k = 0; k < 2; k++) {
                glm::vec3 weightVector(u - i, v - j, w - k);
                sum += (i * uu + (1 - i) * (1 - uu)) *
                       (j * vv + (1 - j) * (1 - vv)) *
                       (k * ww + (1 - k) * (1 - ww)) *
                       glm::dot(c[i][j][k], weightVector);
            }

    return sum;
}
