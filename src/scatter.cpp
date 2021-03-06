#include "scatter.h"
#include "utils.h"
#include <cmath>

vec3 getColor(const HitRecord &hitRecord) {
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
    vec3 scatterDirection = (hitRecord.normal + getRandomUnitVector()).normalized();

    if (isNearZero(scatterDirection)) {
        scatterDirection = hitRecord.normal;
    }

    return {true, getColor(hitRecord), {hitRecord.point, scatterDirection}};
}

ScatterInfo scatterMetal(const Ray &ray, const HitRecord &hitRecord) {
    vec3 scatterDirection = reflect(ray.direction, hitRecord.normal);

    return {true, getColor(hitRecord), {hitRecord.point, scatterDirection}};
}

ScatterInfo scatterDielectric(const Ray &ray, const HitRecord &hitRecord) {
    float refractionRatio = hitRecord.isFrontFace ? (1.0f / hitRecord.material.refractionIndex)
                                                  : hitRecord.material.refractionIndex;
    vec3 scatterDirection = refract(ray.direction, hitRecord.normal, refractionRatio);

    return {true, vec3{1.0f, 1.0f, 1.0f}, {hitRecord.point, scatterDirection}};
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
