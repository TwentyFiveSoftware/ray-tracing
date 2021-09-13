#include "sphere.h"
#include "../utils/onb.h"

#include <utility>

Sphere::Sphere() : center(), radius() {}

Sphere::Sphere(glm::vec3 center, float radius, std::shared_ptr<Material> material) :
        center(center), radius(radius), materialPtr(std::move(material)) {}

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
    record.materialPtr = materialPtr;
    record.uv = getSphereUV(outwardNormal);

    return true;
}

bool Sphere::boundingBox(AABB &outputBox) const {
    outputBox = AABB(
            center - glm::vec3(radius, radius, radius),
            center + glm::vec3(radius, radius, radius)
    );

    return true;
}

glm::vec2 Sphere::getSphereUV(const glm::vec3 &point) {
    auto phi = std::atan2(point.z, point.x) + PI;
    auto theta = std::acos(point.y);

    float u = phi / (2 * PI);
    float v = theta / PI;
    return {u, v};
}

float Sphere::pdfValue(const glm::vec3 &origin, const glm::vec3 &direction) const {
    HitRecord record = {};

    if (!hit(Ray(origin, direction), 0.001f, INFINITY, record))
        return 0.0f;

    float distance = glm::length(center - origin);
    float cosThetaMax = std::sqrt(1.0f - radius * radius / (distance * distance));
    float solidAngle = 2.0f * PI * (1.0f - cosThetaMax);

    return 1.0f / solidAngle;
}

glm::vec3 Sphere::randomPoint(const glm::vec3 &origin) const {
    const glm::vec3 direction = center - origin;
    return OrthonormalBasis(direction).local(randomToSphere(radius, glm::length(direction)));
}
