#pragma once

#define STB_IMAGE_IMPLEMENTATION

#include "texture.h"
#include <string>

class TextureImage : public Texture {
public:
    TextureImage();

    explicit TextureImage(const std::string &filename);

    ~TextureImage();

    [[nodiscard]] glm::vec3 value(const glm::vec2 &uv, const glm::vec3 &point) const override;

private:
    unsigned char* data;
    int width, height, channels;

};
