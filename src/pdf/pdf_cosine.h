#pragma once

#include "pdf.h"
#include "../utils/onb.h"

class PdfCosine : public PDF {
public:
    PdfCosine(const glm::vec3 &n);

    [[nodiscard]] float value(const glm::vec3 &direction) const override;

    [[nodiscard]] glm::vec3 generate() const override;

private:
    OrthonormalBasis onb;

};
