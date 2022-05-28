#pragma once

#include <vector>
#include <array>
#include "sphere.h"

class Scene {
public:
    Scene();

    [[nodiscard]] const std::vector<Sphere>* getSpheres() const;

private:
    std::vector<Sphere> spheres;
};
