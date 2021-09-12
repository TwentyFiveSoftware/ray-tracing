#include "material.h"

class MaterialRefractive : public Material {
public:
    MaterialRefractive(float refractionIndex);

    [[nodiscard]] ScatterInfo scatter(const Ray &ray, const glm::vec3 &pos, const glm::vec3 &normal,
                                      const glm::vec2 &uv, bool frontFace) const override;

private:
    float refractionIndex;

};
