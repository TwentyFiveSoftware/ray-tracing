#include "material.h"
#include <memory>
#include "../texture/texture.h"

class MaterialIsotropic : public Material {
public:
    MaterialIsotropic(std::shared_ptr<Texture> albedo);

    [[nodiscard]] ScatterInfo scatter(const Ray &ray, const glm::vec3 &pos, const glm::vec3 &normal,
                                      const glm::vec2 &uv, bool frontFace) const override;

private:
    std::shared_ptr<Texture> albedo;

};
