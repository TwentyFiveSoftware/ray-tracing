#include "material_metal.h"
#include "../utils/utils.h"

MaterialMetal::MaterialMetal(const glm::vec3 &albedo, float fuzz) :
        albedo(albedo), fuzz(std::min(fuzz, 1.0f)) {}

bool MaterialMetal::scatter(ScatterRecord &scatterRecord, const Ray &ray, const glm::vec3 &pos,
                            const glm::vec3 &normal, const glm::vec2 &uv, bool frontFace) const {

    glm::vec3 reflectedVector = reflectVector(ray.getNormalizedDirection(), normal);

    scatterRecord.attenuation = albedo;
    scatterRecord.isSpecular = true;
    scatterRecord.specularRay = Ray(pos, reflectedVector + fuzz * getRandomPointInUnitSphere());
    scatterRecord.pdf = nullptr;

    return true;
}
