#pragma once

#include <vector>
#include "sphere.h"

class Scene {
public:
    Scene();

    [[nodiscard]] std::vector<Sphere> getSpheres() const;

private:
    std::vector<Sphere> spheres;
};
