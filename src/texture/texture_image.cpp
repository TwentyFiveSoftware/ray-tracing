#include "texture_image.h"
#include <stb_image.h>
#include <iostream>
#include <algorithm>

TextureImage::TextureImage() :
        data(), width(), height(), channels() {}

TextureImage::TextureImage(const std::string &filename) :
        data(), width(), height(), channels() {

    data = stbi_load(filename.c_str(), &width, &height, &channels, 3);

    if (!data)
        std::cerr << "Error: Could not load texture image file '" << filename << "'" << std::endl;
}

TextureImage::~TextureImage() {
    delete data;
}

glm::vec3 TextureImage::value(const glm::vec2 &uv, const glm::vec3 &point) const {
    if (!data)
        return glm::vec3(0.0f, 1.0f, 1.0f);

    auto i = static_cast<int>(std::clamp(uv.x, 0.0f, 1.0f) * float(width));
    auto j = static_cast<int>(std::clamp(uv.y, 0.0f, 1.0f) * float(height));

    i = std::min(i, width - 1);
    j = std::min(j, height - 1);

    auto pixel = data + (j * width + i) * channels;
    return glm::vec3(float(pixel[0]) / 0xFF, float(pixel[1]) / 0xFF, float(pixel[2]) / 0xFF);
}
