#include "material.h"
#include <memory>
#include "../texture/texture.h"

class MaterialDiffuse : public Material {
public:
    explicit MaterialDiffuse(const glm::vec3 &albedo);

    explicit MaterialDiffuse(std::shared_ptr<Texture> texture);

    [[nodiscard]] bool scatter(ScatterRecord &scatterRecord, const Ray &ray, const glm::vec3 &pos,
                               const glm::vec3 &normal, const glm::vec2 &uv, bool frontFace) const override;

    [[nodiscard]] float scatteringPdf(const Ray &ray, const glm::vec3 &normal, const Ray &scatteredRay) const override;

private:
    std::shared_ptr<Texture> albedo;

};
