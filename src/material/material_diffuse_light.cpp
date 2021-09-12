#include "material_diffuse_light.h"
#include <utility>
#include "../texture/texture_solid_color.h"

MaterialDiffuseLight::MaterialDiffuseLight(const glm::vec3 &emission) :
emission(std::make_shared<TextureSolidColor>(emission)) {}

MaterialDiffuseLight::MaterialDiffuseLight(std::shared_ptr<Texture> texture) :
        emission(std::move(texture)) {}

ScatterInfo MaterialDiffuseLight::scatter(const Ray &ray, const glm::vec3 &pos, const glm::vec3 &normal,
                                          const glm::vec2 &uv, bool frontFace) const {
     return {.doesScatter = false};
}

glm::vec3 MaterialDiffuseLight::emitted(const glm::vec3 &pos, const glm::vec2 &uv) const {
    return emission->value(uv, pos);
}
