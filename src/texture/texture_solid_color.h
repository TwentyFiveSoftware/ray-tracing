#pragma once

#include "texture.h"

class TextureSolidColor : public Texture {
public:
    explicit TextureSolidColor(glm::vec3 color);

    [[nodiscard]] glm::vec3 value(const glm::vec2 &uv, const glm::vec3 &point) const override;

private:
    glm::vec3 color;

};
