#pragma once

#include <memory>
#include "../ray.h"
#include "../pdf/pdf.h"

struct ScatterRecord {
    bool isSpecular;
    glm::vec3 attenuation;
    Ray specularRay;
    std::shared_ptr<PDF> pdf;
};
