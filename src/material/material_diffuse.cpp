#include "material_diffuse.h"
#include <utility>
#include "../utils/utils.h"
#include "../texture/texture_solid_color.h"
#include "../pdf/pdf_cosine.h"

MaterialDiffuse::MaterialDiffuse(const glm::vec3 &albedo) :
        albedo(std::make_shared<TextureSolidColor>(albedo)) {}

MaterialDiffuse::MaterialDiffuse(std::shared_ptr<Texture> texture) :
        albedo(std::move(texture)) {}

bool MaterialDiffuse::scatter(ScatterRecord &scatterRecord, const Ray &ray, const glm::vec3 &pos,
                              const glm::vec3 &normal, const glm::vec2 &uv, bool frontFace) const {

    scatterRecord.isSpecular = false;
    scatterRecord.attenuation = albedo->value(uv, pos);
    scatterRecord.pdf = std::make_shared<PdfCosine>(normal);

    return true;
}

float MaterialDiffuse::scatteringPdf(const Ray &ray, const glm::vec3 &normal, const Ray &scatteredRay) const {
    float cosine = glm::dot(normal, scatteredRay.getNormalizedDirection());
    return cosine < 0.0f ? 0.0f : cosine / PI;
}
