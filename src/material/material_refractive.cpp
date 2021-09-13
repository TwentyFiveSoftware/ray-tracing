#include "material_refractive.h"
#include "../utils/utils.h"

MaterialRefractive::MaterialRefractive(float refractionIndex) :
        refractionIndex(refractionIndex) {}

bool MaterialRefractive::scatter(ScatterRecord &scatterRecord, const Ray &ray, const glm::vec3 &pos,
                                 const glm::vec3 &normal, const glm::vec2 &uv, bool frontFace) const {
    float refractionIndexRatio = frontFace ? (1.0f / refractionIndex) : refractionIndex;
    glm::vec3 scatteredRayDirection;

    bool doesRefract =
            canRefract(ray.getNormalizedDirection(), normal, refractionIndexRatio) &&
            reflectanceFactorApproximation(ray.getNormalizedDirection(), normal, refractionIndexRatio) < randomFloat();

    if (doesRefract)
        scatteredRayDirection = refractVector(ray.getNormalizedDirection(), normal, refractionIndexRatio);
    else
        scatteredRayDirection = reflectVector(ray.getNormalizedDirection(), normal);

    scatterRecord.isSpecular = true;
    scatterRecord.attenuation = glm::vec3(1.0f, 1.0f, 1.0f);
    scatterRecord.pdf = nullptr;
    scatterRecord.specularRay = Ray(pos, scatteredRayDirection);

    return true;
}
