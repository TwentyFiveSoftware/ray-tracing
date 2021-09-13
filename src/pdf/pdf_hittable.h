#pragma once

#include "pdf.h"
#include <memory>
#include "../objects/hittable.h"

class PdfHittable : public PDF {
public:
    PdfHittable(std::shared_ptr<Hittable> object, const glm::vec3 &origin);

    [[nodiscard]] float value(const glm::vec3 &direction) const override;

    [[nodiscard]] glm::vec3 generate() const override;

private:
    std::shared_ptr<Hittable> object;
    glm::vec3 origin;

};
