#pragma once

#include <memory>
#include "texture.h"
#include "texture_solid_color.h"

class TextureCheckered : public Texture {
public:
    TextureCheckered(float size, std::shared_ptr<TextureSolidColor> evenTexture,
                     std::shared_ptr<TextureSolidColor> oddTexture);

    [[nodiscard]] glm::vec3 value(const glm::vec2 &uv, const glm::vec3 &point) const override;

private:
    float size;
    std::shared_ptr<TextureSolidColor> evenTexture, oddTexture;

};
