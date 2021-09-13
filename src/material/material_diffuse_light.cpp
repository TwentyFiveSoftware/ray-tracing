#include "material_diffuse_light.h"
#include <utility>
#include "../texture/texture_solid_color.h"

MaterialDiffuseLight::MaterialDiffuseLight(const glm::vec3 &emission) :
        emission(std::make_shared<TextureSolidColor>(emission)) {}

MaterialDiffuseLight::MaterialDiffuseLight(std::shared_ptr<Texture> texture) :
        emission(std::move(texture)) {}

bool MaterialDiffuseLight::scatter(ScatterRecord &scatterRecord, const Ray &ray, const glm::vec3 &pos,
                                   const glm::vec3 &normal, const glm::vec2 &uv, bool frontFace) const {
    return false;
}

glm::vec3 MaterialDiffuseLight::emitted(const Ray &ray, const glm::vec3 &pos, const glm::vec2 &uv,
                                        bool frontFace) const {
    return frontFace ? emission->value(uv, pos) : glm::vec3(0.0f, 0.0f, 0.0f);
}
