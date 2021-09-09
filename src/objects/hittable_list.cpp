#include "hittable_list.h"

HittableList::HittableList() = default;

void HittableList::clear() {
    objects.clear();
}

void HittableList::add(const std::shared_ptr<Hittable> &object) {
    objects.push_back(object);
}

bool HittableList::hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const {
    HitRecord tempRecord = {};
    bool hitAnything = false;
    float closestObjectT = tMax;

    for (const auto &object : objects) {
        if (object->hit(ray, tMin, closestObjectT, tempRecord)) {
            hitAnything = true;
            closestObjectT = tempRecord.t;
            record = tempRecord;
        }
    }

    return hitAnything;
}
