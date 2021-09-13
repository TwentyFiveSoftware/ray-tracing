#include "rect_yz.h"
#include "../utils/utils.h"

RectangleYZ::RectangleYZ() :
        y0(), y1(), z0(), z1(), x() {}

RectangleYZ::RectangleYZ(float y0, float y1, float z0, float z1, float x, std::shared_ptr<Material> material) :
        y0(y0), y1(y1), z0(z0), z1(z1), x(x), materialPtr(std::move(material)) {}

bool RectangleYZ::hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const {
    float t = (x - ray.getOrigin().x) / ray.getDirection().x;

    if (t < tMin || t > tMax)
        return false;

    float y = ray.at(t).y;
    float z = ray.at(t).z;

    if (y < y0 || y > y1 || z < z0 || z > z1)
        return false;

    record.uv = glm::vec2((y - y0) / (y1 - y0), (z - z0) / (z1 - z0));
    record.t = t;
    record.setFaceNormal(ray, glm::vec3(1.0f, 0.0f, 0.0f));
    record.materialPtr = materialPtr;
    record.pos = ray.at(t);

    return true;
}

bool RectangleYZ::boundingBox(AABB &outputBox) const {
    outputBox = AABB(
            glm::vec3(x - 0.0001f, y0, z0),
            glm::vec3(x + 0.0001f, y1, z1)
    );

    return true;
}

float RectangleYZ::pdfValue(const glm::vec3 &origin, const glm::vec3 &direction) const {
    HitRecord record = {};

    if (!hit(Ray(origin, direction), 0.001f, INFINITY, record))
        return 0.0f;

    float area = (y1 - y0) * (z1 - z0);
    float distance = record.t * glm::length(direction);
    float cosine = std::abs(glm::dot(direction, record.normal) / glm::length(direction));

    return distance * distance / (cosine * area);
}

glm::vec3 RectangleYZ::randomPoint(const glm::vec3 &origin) const {
    glm::vec3 randomPoint = glm::vec3(x, randomFloat(y0, y1), randomFloat(z0, z1));
    return randomPoint - origin;
}
