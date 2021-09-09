#pragma once

#include <vector>
#include <memory>
#include "hittable.h"

class HittableList : public Hittable {
public:
    HittableList();

    void clear();

    void add(const std::shared_ptr<Hittable> &object);

    bool hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const override;

private:
    std::vector<std::shared_ptr<Hittable>> objects;

};
