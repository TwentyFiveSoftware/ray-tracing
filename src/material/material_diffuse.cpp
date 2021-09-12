#include "material_diffuse.h"
#include <utility>
#include "../utils.h"
#include "../texture/texture_solid_color.h"

MaterialDiffuse::MaterialDiffuse(const glm::vec3 &albedo) :
        albedo(std::make_shared<TextureSolidColor>(albedo)) {}

MaterialDiffuse::MaterialDiffuse(std::shared_ptr<Texture> texture) :
        albedo(std::move(texture)) {}

ScatterInfo MaterialDiffuse::scatter(const Ray &ray, const glm::vec3 &pos, const glm::vec3 &normal, const glm::vec2 &uv,
                                     bool frontFace) const {
    glm::vec3 scatterDirection = normal + getRandomUnitVector();

    if (isVectorNearZero(scatterDirection))
        scatterDirection = normal;

    return {
            .doesScatter = true,
            .attenuation = albedo->value(uv, pos),
            .scatteredRay = Ray(pos, scatterDirection)
    };
}
