#pragma once

#include "texture.h"

class TextureSolidColor : public Texture {
public:
    explicit TextureSolidColor(glm::vec3 color) :
            color(color) {}

    [[nodiscard]] glm::vec3 value(const glm::vec2 &uv, const glm::vec3 &point) const override {
        return color;
    }

private:
    glm::vec3 color;

};
