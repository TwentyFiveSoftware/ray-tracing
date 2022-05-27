#include "sphere.h"

Sphere::Sphere() : center(), radius() {}

Sphere::Sphere(const glm::vec3 &center, float radius) : center(center), radius(radius) {}

HitRecord Sphere::rayHitsSphere(const Ray &ray, float tMin, float tMax) const {
    glm::vec3 oc = ray.getOrigin() - center;
    float a = glm::dot(ray.getDirection(), ray.getDirection());
    float halfB = glm::dot(oc, ray.getDirection());
    float c = glm::dot(oc, oc) - radius * radius;
    float discriminant = halfB * halfB - a * c;

    if (discriminant < 0.0f) {
        return {};
    }

    float sqrtD = std::sqrt(discriminant);
    float t = (-halfB - sqrtD) / a;
    if (t < tMin || t > tMax) {
        t = (-halfB + sqrtD) / a;

        if (t < tMin || t > tMax) {
            return {};
        }
    }

    glm::vec3 point = ray.at(t);
    glm::vec3 normal = (point - center) / radius;
    bool isFrontFace = glm::dot(ray.getDirection(), normal) < 0.0;

    return {
            .hit = true,
            .t = t,
            .point = point,
            .normal = normal,
            .isFrontFace = isFrontFace
    };
}
