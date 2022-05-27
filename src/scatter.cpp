#include "scatter.h"
#include "utils.h"

ScatterInfo scatterDiffuse(const Ray &ray, const HitRecord &hitRecord) {
    glm::vec3 scatterDirection = glm::normalize(hitRecord.normal + getRandomUnitVector());

    if (isNearZero(scatterDirection)) {
        scatterDirection = hitRecord.normal;
    }

    return {true, hitRecord.material.albedo, Ray(hitRecord.point, scatterDirection)};
}

ScatterInfo scatterMetal(const Ray &ray, const HitRecord &hitRecord) {
    glm::vec3 scatterDirection = reflect(glm::normalize(ray.getDirection()), hitRecord.normal);

    return {true, hitRecord.material.albedo, Ray(hitRecord.point, scatterDirection)};
}

ScatterInfo scatterDielectric(const Ray &ray, const HitRecord &hitRecord) {
    float refractionRatio = hitRecord.isFrontFace ? (1.0f / hitRecord.material.refractionIndex)
                                                  : hitRecord.material.refractionIndex;
    glm::vec3 scatterDirection = refract(glm::normalize(ray.getDirection()), hitRecord.normal, refractionRatio);

    return {true, glm::vec3(1.0f, 1.0f, 1.0f), Ray(hitRecord.point, scatterDirection)};
}

ScatterInfo scatter(const Ray &ray, const HitRecord &hitRecord) {
    switch (hitRecord.material.type) {
        case DIFFUSE:
            return scatterDiffuse(ray, hitRecord);
        case METAL:
            return scatterMetal(ray, hitRecord);
        case DIELECTRIC:
            return scatterDielectric(ray, hitRecord);
    }
}
