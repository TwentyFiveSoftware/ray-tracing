#pragma once

#include "hittable.h"
#include "hittable_list.h"

class BVHNode : public Hittable {
public:
    BVHNode(const HittableList &objects);

    BVHNode(const std::vector<std::shared_ptr<Hittable>> &srcObjects, size_t start, size_t end);

    bool hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const override;

    bool boundingBox(AABB &outputBox) const override;

private:
    std::shared_ptr<Hittable> leftNode;
    std::shared_ptr<Hittable> rightNode;
    AABB box;

};
