#include "texture_solid_color.h"

TextureSolidColor::TextureSolidColor(glm::vec3 color) :
        color(color) {}

glm::vec3 TextureSolidColor::value(const glm::vec2 &uv, const glm::vec3 &point) const {
    return color;
}
