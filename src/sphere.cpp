#include "sphere.h"

Sphere::Sphere() : center(), radius(), material() {}

Sphere::Sphere(const glm::vec3 &center, float radius, const Material &material)
        : center(center), radius(radius), material(material) {}

HitRecord Sphere::rayHitsSphere(const Ray &ray, float tMin, float tMax) const {
    const glm::vec3 oc = ray.direction - center;
    float a = glm::dot(ray.direction, ray.direction);
    float halfB = glm::dot(oc, ray.direction);
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

    const glm::vec3 point = rayAt(ray, t);
    const glm::vec3 normal = (point - center) / radius;
    bool isFrontFace = glm::dot(ray.direction, normal) < 0.0;

    return {
            .hit = true,
            .t = t,
            .point = point,
            .normal = normal,
            .isFrontFace = isFrontFace,
            .material = material,
    };
}
