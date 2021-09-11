#include "material_refractive.h"
#include "../utils.h"

MaterialRefractive::MaterialRefractive(float refractionIndex) :
        refractionIndex(refractionIndex) {}

ScatterInfo MaterialRefractive::scatter(const Ray &ray, const glm::vec3 &pos, const glm::vec3 &normal,
                                        bool frontFace) const {
    float refractionIndexRatio = frontFace ? (1.0f / refractionIndex) : refractionIndex;
    glm::vec3 scatteredRayDirection;

    bool doesRefract =
            canRefract(ray.getNormalizedDirection(), normal, refractionIndexRatio) &&
            reflectanceFactorApproximation(ray.getNormalizedDirection(), normal, refractionIndexRatio) < randomFloat();

    if (doesRefract)
        scatteredRayDirection = refractVector(ray.getNormalizedDirection(), normal, refractionIndexRatio);
    else
        scatteredRayDirection = reflectVector(ray.getNormalizedDirection(), normal);

    return {
            .doesScatter = true,
            .attenuation = glm::vec3(1.0f, 1.0f, 1.0f),
            .scatteredRay = Ray(pos, scatteredRayDirection)
    };
}
