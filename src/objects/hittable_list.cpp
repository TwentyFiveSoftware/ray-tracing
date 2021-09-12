#include "hittable_list.h"
#include "../utils/utils.h"

HittableList::HittableList() = default;

void HittableList::clear() {
    objects.clear();
}

void HittableList::add(const std::shared_ptr<Hittable> &object) {
    objects.push_back(object);
}

std::vector<std::shared_ptr<Hittable>> HittableList::getObjects() const {
    return objects;
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

bool HittableList::boundingBox(AABB &outputBox) const {
    if (objects.empty())
        return false;

    AABB tempBox;
    bool isFirstBox = true;

    for (const auto &object : objects) {
        if (!object->boundingBox(tempBox))
            return false;

        outputBox = isFirstBox ? tempBox : calculateSurroundingBox(outputBox, tempBox);
        isFirstBox = false;
    }

    return true;
}
