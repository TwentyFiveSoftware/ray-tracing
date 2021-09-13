#include "pdf_hittable.h"
#include <utility>

PdfHittable::PdfHittable(std::shared_ptr<Hittable> object, const glm::vec3 &origin) :
        object(std::move(object)), origin(origin) {}

float PdfHittable::value(const glm::vec3 &direction) const {
    return object->pdfValue(origin, direction);
}

glm::vec3 PdfHittable::generate() const {
    return object->randomPoint(origin);
}
