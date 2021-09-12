#include "x_aa_rect.h"

XAxisAlignedRectangle::XAxisAlignedRectangle() :
        y0(), y1(), z0(), z1(), x() {}

XAxisAlignedRectangle::XAxisAlignedRectangle(float y0, float y1, float z0, float z1, float x,
                                             std::shared_ptr<Material> material) :
        y0(y0), y1(y1), z0(z0), z1(z1), x(x), materialPtr(std::move(material)) {}

bool XAxisAlignedRectangle::hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const {
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

bool XAxisAlignedRectangle::boundingBox(AABB &outputBox) const {
    outputBox = AABB(
            glm::vec3(x - 0.0001f, y0, z0),
            glm::vec3(x + 0.0001f, y1, z1)
    );

    return true;
}
