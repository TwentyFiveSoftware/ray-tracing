#include "material_isotropic.h"
#include <utility>
#include "../utils/utils.h"

MaterialIsotropic::MaterialIsotropic(std::shared_ptr<Texture> albedo) :
        albedo(std::move(albedo)) {}

bool MaterialIsotropic::scatter(ScatterRecord &scatterRecord, const Ray &ray, const glm::vec3 &pos,
                                const glm::vec3 &normal, const glm::vec2 &uv, bool frontFace) const {

    scatterRecord.attenuation = albedo->value(uv, pos);
    scatterRecord.isSpecular = true;
    scatterRecord.specularRay = Ray(pos, getRandomPointInUnitSphere());
    scatterRecord.pdf = nullptr;

    return true;
}
