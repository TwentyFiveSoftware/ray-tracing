#include "scatter.h"
#include "utils.h"

glm::vec3 getColor(const HitRecord &hitRecord) {
    switch (hitRecord.material.textureType) {
        case SOLID:
            return hitRecord.material.albedo;
        case CHECKERED:
            float size = 6.0f;
            float sin = std::sin(size * hitRecord.point.x) * std::sin(size * hitRecord.point.y) *
                        std::sin(size * hitRecord.point.z);
            return sin < 0.0f ? hitRecord.material.albedo : hitRecord.material.albedo2;
    }

    return {0.0f, 0.0f, 0.0f};
}

ScatterInfo scatterDiffuse(const Ray &ray, const HitRecord &hitRecord) {
    glm::vec3 scatterDirection = glm::normalize(hitRecord.normal + getRandomUnitVector());

    if (isNearZero(scatterDirection)) {
        scatterDirection = hitRecord.normal;
    }

    return {true, getColor(hitRecord), Ray(hitRecord.point, scatterDirection)};
}

ScatterInfo scatterMetal(const Ray &ray, const HitRecord &hitRecord) {
    glm::vec3 scatterDirection = reflect(glm::normalize(ray.getDirection()), hitRecord.normal);

    return {true, getColor(hitRecord), Ray(hitRecord.point, scatterDirection)};
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

    return {};
}
