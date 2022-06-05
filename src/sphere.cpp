#include "sphere.h"
#include <cmath>

Sphere::Sphere() : center(), radius(), material() {}

Sphere::Sphere(const vec3 &center, float radius, const Material &material)
        : center(center), radius(radius), material(material) {}

HitRecord Sphere::rayHitsSphere(const Ray &ray, float tMin, float tMax) const {
    const vec3 oc = ray.origin - center;
    float a = ray.direction.dot(ray.direction);
    float halfB = oc.dot(ray.direction);
    float c = oc.dot(oc) - radius * radius;
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

    const vec3 point = rayAt(ray, t);
    const vec3 normal = (point - center) / radius;
    bool isFrontFace = ray.direction.dot(normal) < 0.0;

    return {
            .hit = true,
            .t = t,
            .point = point,
            .normal = normal,
            .isFrontFace = isFrontFace,
            .material = material,
    };
}
