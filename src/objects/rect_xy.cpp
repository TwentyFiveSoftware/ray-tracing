#include "rect_xy.h"
#include "../utils/utils.h"

RectangleXY::RectangleXY() :
        x0(), x1(), y0(), y1(), z() {}

RectangleXY::RectangleXY(float x0, float x1, float y0, float y1, float z, std::shared_ptr<Material> material) :
        x0(x0), x1(x1), y0(y0), y1(y1), z(z), materialPtr(std::move(material)) {}

bool RectangleXY::hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const {
    float t = (z - ray.getOrigin().z) / ray.getDirection().z;

    if (t < tMin || t > tMax)
        return false;

    float x = ray.at(t).x;
    float y = ray.at(t).y;

    if (x < x0 || x > x1 || y < y0 || y > y1)
        return false;

    record.uv = glm::vec2((x - x0) / (x1 - x0), (y - y0) / (y1 - y0));
    record.t = t;
    record.setFaceNormal(ray, glm::vec3(0.0f, 0.0f, 1.0f));
    record.materialPtr = materialPtr;
    record.pos = ray.at(t);

    return true;
}

bool RectangleXY::boundingBox(AABB &outputBox) const {
    outputBox = AABB(
            glm::vec3(x0, y0, z - 0.0001f),
            glm::vec3(x1, y1, z + 0.0001f)
    );

    return true;
}

float RectangleXY::pdfValue(const glm::vec3 &origin, const glm::vec3 &direction) const {
    HitRecord record = {};

    if (!hit(Ray(origin, direction), 0.001f, INFINITY, record))
        return 0.0f;

    float area = (x1 - x0) * (y1 - y0);
    float distance = record.t * glm::length(direction);
    float cosine = std::abs(glm::dot(direction, record.normal) / glm::length(direction));

    return distance * distance / (cosine * area);
}

glm::vec3 RectangleXY::randomPoint(const glm::vec3 &origin) const {
    glm::vec3 randomPoint = glm::vec3(randomFloat(x0, x1), randomFloat(y0, y1), z);
    return randomPoint - origin;
}
