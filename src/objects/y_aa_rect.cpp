#include "y_aa_rect.h"

YAxisAlignedRectangle::YAxisAlignedRectangle() :
        x0(), x1(), z0(), z1(), y() {}

YAxisAlignedRectangle::YAxisAlignedRectangle(float x0, float x1, float z0, float z1, float y,
                                             std::shared_ptr<Material> material) :
        x0(x0), x1(x1), z0(z0), z1(z1), y(y), materialPtr(std::move(material)) {}

bool YAxisAlignedRectangle::hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const {
    float t = (y - ray.getOrigin().y) / ray.getDirection().y;

    if (t < tMin || t > tMax)
        return false;

    float x = ray.at(t).x;
    float z = ray.at(t).z;

    if (x < x0 || x > x1 || z < z0 || z > z1)
        return false;

    record.uv = glm::vec2((x - x0) / (x1 - x0), (z - z0) / (z1 - z0));
    record.t = t;
    record.setFaceNormal(ray, glm::vec3(0.0f, 1.0f, 0.0f));
    record.materialPtr = materialPtr;
    record.pos = ray.at(t);

    return true;
}

bool YAxisAlignedRectangle::boundingBox(AABB &outputBox) const {
    outputBox = AABB(
            glm::vec3(x0, y - 0.0001f, z0),
            glm::vec3(x1, y + 0.0001f, z1)
    );

    return true;
}
