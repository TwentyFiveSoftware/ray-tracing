#pragma once

#include "pdf.h"
#include <memory>
#include "../objects/hittable.h"

class PdfMixture : public PDF {
public:
    PdfMixture(std::shared_ptr<PDF> pdf0, std::shared_ptr<PDF> pdf1);

    [[nodiscard]] float value(const glm::vec3 &direction) const override;

    [[nodiscard]] glm::vec3 generate() const override;

private:
    std::shared_ptr<PDF> pdf0;
    std::shared_ptr<PDF> pdf1;

};
