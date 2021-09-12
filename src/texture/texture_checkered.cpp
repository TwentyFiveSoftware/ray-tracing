#include "texture_solid_color.h"
#include "texture_checkered.h"
#include <utility>
#include "../utils.h"

TextureCheckered::TextureCheckered(
        float size, std::shared_ptr<TextureSolidColor> evenTexture, std::shared_ptr<TextureSolidColor> oddTexture) :
        size(2.0f * PI / size), evenTexture(std::move(evenTexture)), oddTexture(std::move(oddTexture)) {}

glm::vec3 TextureCheckered::value(const glm::vec2 &uv, const glm::vec3 &point) const {
    float sines = std::sin(size * point.x) * std::sin(size * point.y) * std::sin(size * point.z);
    return sines < 0 ?
           oddTexture->value(uv, point) :
           evenTexture->value(uv, point);
}
