#include "z_aa_rect.h"

ZAxisAlignedRectangle::ZAxisAlignedRectangle() :
        x0(), x1(), y0(), y1(), z() {}

ZAxisAlignedRectangle::ZAxisAlignedRectangle(float x0, float x1, float y0, float y1, float z,
                                             std::shared_ptr<Material> material) :
        x0(x0), x1(x1), y0(y0), y1(y1), z(z), materialPtr(std::move(material)) {}

bool ZAxisAlignedRectangle::hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const {
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

bool ZAxisAlignedRectangle::boundingBox(AABB &outputBox) const {
    outputBox = AABB(
            glm::vec3(x0, y0, z - 0.0001f),
            glm::vec3(x1, y1, z + 0.0001f)
    );

    return true;
}
