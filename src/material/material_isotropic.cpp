#include "material_isotropic.h"
#include <utility>
#include "../utils/utils.h"

MaterialIsotropic::MaterialIsotropic(std::shared_ptr<Texture> albedo) :
        albedo(std::move(albedo)) {}

ScatterInfo MaterialIsotropic::scatter(const Ray &ray, const glm::vec3 &pos, const glm::vec3 &normal,
                                       const glm::vec2 &uv, bool frontFace) const {
    return {
            .doesScatter = true,
            .attenuation = albedo->value(uv, pos),
            .scatteredRay = Ray(pos, getRandomPointInUnitSphere())
    };
}
