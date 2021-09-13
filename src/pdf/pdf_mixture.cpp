#include "pdf_mixture.h"
#include <utility>
#include "../utils/utils.h"

PdfMixture::PdfMixture(std::shared_ptr<PDF> pdf0, std::shared_ptr<PDF> pdf1) :
        pdf0(std::move(pdf0)), pdf1(std::move(pdf1)) {}

float PdfMixture::value(const glm::vec3 &direction) const {
    return 0.5f * pdf0->value(direction) + 0.5f * pdf1->value(direction);
}

glm::vec3 PdfMixture::generate() const {
    return randomFloat() < 0.5f ? pdf0->generate() : pdf1->generate();
}
