#include "ray.h"

glm::vec3 rayAt(const Ray &ray, float t) {
    return ray.origin + ray.direction * t;
}
