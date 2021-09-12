#include "material_metal.h"
#include "../utils.h"

MaterialMetal::MaterialMetal(const glm::vec3 &albedo, float fuzz) :
        albedo(albedo), fuzz(std::min(fuzz, 1.0f)) {}

ScatterInfo MaterialMetal::scatter(const Ray &ray, const glm::vec3 &pos, const glm::vec3 &normal,
                                   const glm::vec2 &uv, bool frontFace) const {
    glm::vec3 reflectedVector = reflectVector(ray.getNormalizedDirection(), normal);
    Ray scatteredRay = Ray(pos, reflectedVector + fuzz * getRandomPointInUnitSphere());

    return {
            .doesScatter = dot(scatteredRay.getDirection(), normal) > 0,
            .attenuation = albedo,
            .scatteredRay = scatteredRay
    };
}
