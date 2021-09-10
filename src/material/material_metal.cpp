#include "material_metal.h"
#include "../utils.h"

MaterialMetal::MaterialMetal(const glm::vec3 &albedo) :
        albedo(albedo) {}

ScatterInfo MaterialMetal::scatter(const Ray &ray, const glm::vec3 &pos, const glm::vec3 &normal) const {
    glm::vec3 reflectedVector = reflectVector(glm::normalize(ray.getDirection()), normal);
    Ray scatteredRay = Ray(pos, reflectedVector);

    return {
            .doesScatter = dot(scatteredRay.getDirection(), normal) > 0,
            .attenuation = albedo,
            .scatteredRay = scatteredRay
    };
}
