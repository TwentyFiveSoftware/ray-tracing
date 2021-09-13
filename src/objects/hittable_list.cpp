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

float HittableList::pdfValue(const glm::vec3 &origin, const glm::vec3 &direction) const {
    float weight = 1.0f / float(objects.size());
    float sum = 0.0f;

    for (const auto &object : objects)
        sum += weight * object->pdfValue(origin, direction);

    return sum;
}

glm::vec3 HittableList::randomPoint(const glm::vec3 &origin) const {
    auto size = static_cast<int32_t>(objects.size());
    return objects[randomInt(0, size - 1)]->randomPoint(origin);
}
