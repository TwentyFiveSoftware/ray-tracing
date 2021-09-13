#include <memory>
#include "material.h"
#include "../texture/texture.h"

class MaterialDiffuseLight : public Material {
public:
    explicit MaterialDiffuseLight(const glm::vec3 &emission);

    explicit MaterialDiffuseLight(std::shared_ptr<Texture> texture);

    [[nodiscard]] bool scatter(ScatterRecord &scatterRecord, const Ray &ray, const glm::vec3 &pos,
                               const glm::vec3 &normal, const glm::vec2 &uv, bool frontFace) const override;

    [[nodiscard]] glm::vec3 emitted(const Ray &ray, const glm::vec3 &pos, const glm::vec2 &uv,
                                    bool frontFace) const override;

private:
    std::shared_ptr<Texture> emission;

};
