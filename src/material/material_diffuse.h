#include "material.h"
#include <memory>
#include "../texture/texture.h"

class MaterialDiffuse : public Material {
public:
    MaterialDiffuse(const glm::vec3 &albedo);

    MaterialDiffuse(std::shared_ptr<Texture> texture);

    [[nodiscard]] ScatterInfo scatter(const Ray &ray, const glm::vec3 &pos, const glm::vec3 &normal,
                                      const glm::vec2 &uv, bool frontFace) const override;

private:
    std::shared_ptr<Texture> albedo;

};
