#include "bvh_node.h"
#include <algorithm>
#include <iostream>
#include "../utils/utils.h"

inline bool compareBox(const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b, uint8_t axis) {
    AABB boxA, boxB;

    if (!a->boundingBox(boxA) || !b->boundingBox(boxB)) {
        std::cerr << "An object has no bounding box in BVH" << std::endl;
    }

    return boxA.min()[axis] < boxB.min()[axis];
}

bool compareBoxX(const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b) {
    return compareBox(a, b, 0);
}

bool compareBoxY(const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b) {
    return compareBox(a, b, 1);
}

bool compareBoxZ(const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b) {
    return compareBox(a, b, 2);
}

BVHNode::BVHNode(const HittableList &objects) :
        BVHNode(objects.getObjects(), 0, objects.getObjects().size()) {}

BVHNode::BVHNode(const std::vector<std::shared_ptr<Hittable>> &srcObjects, size_t start, size_t end) {
    auto objects = srcObjects;

    uint8_t axis = randomInt(0, 2);
    auto comparator = axis == 0 ? compareBoxX :
                      axis == 1 ? compareBoxY
                                : compareBoxZ;

    size_t objectCount = end - start;

    if (objectCount == 1) {
        leftNode = objects[start];
        rightNode = objects[start];

    } else if (objectCount == 2) {
        if (comparator(objects[start], objects[start + 1])) {
            leftNode = objects[start];
            rightNode = objects[start + 1];
        } else {
            leftNode = objects[start + 1];
            rightNode = objects[start];
        }

    } else {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);

        size_t mid = start + objectCount / 2;
        leftNode = std::make_shared<BVHNode>(objects, start, mid);
        rightNode = std::make_shared<BVHNode>(objects, mid, end);
    }

    AABB leftBox, rightBox;

    if (!leftNode->boundingBox(leftBox) || !rightNode->boundingBox(rightBox)) {
        std::cerr << "No bounding box in left or right node of BVH node" << std::endl;
    }

    box = calculateSurroundingBox(leftBox, rightBox);
}

bool BVHNode::hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const {
    if (!box.hit(ray, tMin, tMax))
        return false;

    bool hitInLeftNode = leftNode->hit(ray, tMin, tMax, record);
    bool hitInRightNode = rightNode->hit(ray, tMin, hitInLeftNode ? record.t : tMax, record);

    return hitInLeftNode || hitInRightNode;
}

bool BVHNode::boundingBox(AABB &outputBox) const {
    outputBox = box;
    return true;
}
