#include "material_diffuse.h"
#include "../utils.h"

MaterialDiffuse::MaterialDiffuse(const glm::vec3 &albedo) :
        albedo(albedo) {}

ScatterInfo MaterialDiffuse::scatter(const Ray &ray, const glm::vec3 &pos, const glm::vec3 &normal) const {
    glm::vec3 scatterDirection = normal + getRandomUnitVector();

    if (isVectorNearZero(scatterDirection))
        scatterDirection = normal;

    return {
            .doesScatter = true,
            .attenuation = albedo,
            .scatteredRay = Ray(pos, scatterDirection)
    };
}
