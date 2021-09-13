#include "pdf_cosine.h"
#include "../utils/utils.h"

glm::vec3 randomCosineDirection() {
    float r1 = randomFloat();
    float r2 = randomFloat();
    float phi = 2 * PI * r1;

    return glm::vec3(
            std::cos(phi) * std::sqrt(r2),
            std::sin(phi) * std::sqrt(r2),
            std::sqrt(1.0f - r2)
    );
}

PdfCosine::PdfCosine(const glm::vec3 &n) :
        onb(OrthonormalBasis(n)) {}

float PdfCosine::value(const glm::vec3 &direction) const {
    float cosine = glm::dot(glm::normalize(direction), onb.getW());
    return cosine < 0.0f ? 0.0f : cosine / PI;
}

glm::vec3 PdfCosine::generate() const {
    return glm::normalize(onb.local(randomCosineDirection()));
}
