#include "box.h"
#include "rect_yz.h"
#include "rect_xz.h"
#include "rect_xy.h"

Box::Box() : boxMin(), boxMax(), sides() {}

Box::Box(const glm::vec3 &point0, const glm::vec3 &point1, const std::shared_ptr<Material> &material) :
        boxMin(point0), boxMax(point1), sides(HittableList()) {

    sides.add(std::make_shared<RectangleXY>(point0.x, point1.x, point0.y, point1.y, point0.z, material));
    sides.add(std::make_shared<RectangleXY>(point0.x, point1.x, point0.y, point1.y, point1.z, material));

    sides.add(std::make_shared<RectangleXZ>(point0.x, point1.x, point0.z, point1.z, point0.y, material));
    sides.add(std::make_shared<RectangleXZ>(point0.x, point1.x, point0.z, point1.z, point1.y, material));

    sides.add(std::make_shared<RectangleYZ>(point0.y, point1.y, point0.z, point1.z, point0.x, material));
    sides.add(std::make_shared<RectangleYZ>(point0.y, point1.y, point0.z, point1.z, point1.x, material));
}

bool Box::hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const {
    return sides.hit(ray, tMin, tMax, record);
}

bool Box::boundingBox(AABB &outputBox) const {
    outputBox = AABB(boxMin, boxMax);
    return true;
}

float Box::pdfValue(const glm::vec3 &origin, const glm::vec3 &direction) const {
    return sides.pdfValue(origin, direction);
}

glm::vec3 Box::randomPoint(const glm::vec3 &origin) const {
    return sides.randomPoint(origin);
}
