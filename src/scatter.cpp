#include "scatter.h"
#include "utils.h"

ScatterInfo scatterDiffuse(const Ray &ray, const HitRecord &hitRecord) {
    glm::vec3 scatterDirection = glm::normalize(hitRecord.normal + getRandomUnitVector());

    if (isNearZero(scatterDirection)) {
        scatterDirection = hitRecord.normal;
    }

    return {
            .doesScatter = true,
            .attenuation = hitRecord.material.albedo,
            .scatteredRay = Ray(hitRecord.point, scatterDirection),
    };
}

ScatterInfo scatterMetal(const Ray &ray, const HitRecord &hitRecord) {
}

ScatterInfo scatter(const Ray &ray, const HitRecord &hitRecord) {
    switch (hitRecord.material.type) {
        case DIFFUSE:
            return scatterDiffuse(ray, hitRecord);
        case METAL:
            return scatterMetal(ray, hitRecord);
    }
}
