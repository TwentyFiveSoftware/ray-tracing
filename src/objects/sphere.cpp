#include "sphere.h"

Sphere::Sphere() : center(), radius() {}

Sphere::Sphere(glm::vec3 center, float radius) :
        center(center), radius(radius) {}

bool Sphere::hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const {
    glm::vec3 co = ray.getOrigin() - center;
    float a = glm::dot(ray.getDirection(), ray.getDirection());
    float half_b = glm::dot(co, ray.getDirection());
    float c = glm::dot(co, co) - radius * radius;
    float discriminant = half_b * half_b - a * c;

    if (discriminant < 0.0f)
        return false;

    float t1 = (-half_b - std::sqrt(discriminant)) / a;
    float t2 = (-half_b + std::sqrt(discriminant)) / a;

    if (t1 >= tMin && t1 <= tMax)
        record.t = t1;
    else if (t2 >= tMin && t2 <= tMax)
        record.t = t2;
    else
        return false;

    record.pos = ray.at(record.t);

    glm::vec3 outwardNormal = (record.pos - center) / radius;
    record.setFaceNormal(ray, outwardNormal);

    return true;
}