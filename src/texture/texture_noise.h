#pragma once

#include "texture.h"
#include "../utils/perlin.h"

class TextureNoise : public Texture {
public:
    TextureNoise() = default;

    explicit TextureNoise(float scale) :
            scale(scale) {};

    [[nodiscard]] glm::vec3 value(const glm::vec2 &uv, const glm::vec3 &point) const override {
        return glm::vec3(1.0f, 1.0f, 1.0f) * 0.5f *
               (1.0f + std::sin(scale * point.z + 10.0f * perlin.turbulence(point, 7)));
    }

//    [[nodiscard]] glm::vec3 value(const glm::vec2 &uv, const glm::vec3 &point) const override {
//        return glm::vec3(1.0f, 1.0f, 1.0f) * perlin.turbulence(point * scale, 7);
//    }

//    [[nodiscard]] glm::vec3 value(const glm::vec2 &uv, const glm::vec3 &point) const override {
//        return glm::vec3(1.0f, 1.0f, 1.0f) * 0.5f * (1.0f + perlin.noise(point * scale));
//    }

private:
    Perlin perlin;
    float scale = 1.0f;

};
