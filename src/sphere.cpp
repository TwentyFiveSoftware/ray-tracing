#include "sphere.h"

Sphere::Sphere() : center(), radius(), material() {}

Sphere::Sphere(const glm::vec3 &center, float radius, const Material &material)
        : center(center), radius(radius), material(material) {}

HitRecord Sphere::rayHitsSphere(const Ray &ray, float tMin, float tMax) const {
    glm::vec3 direction = *ray.getDirection();
    glm::vec3 oc = *ray.getOrigin() - center;
    float a = glm::dot(direction, direction);
    float halfB = glm::dot(oc, direction);
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
    bool isFrontFace = glm::dot(direction, normal) < 0.0;

    return {
            .hit = true,
            .t = t,
            .point = point,
            .normal = normal,
            .isFrontFace = isFrontFace,
            .material = material,
    };
}
