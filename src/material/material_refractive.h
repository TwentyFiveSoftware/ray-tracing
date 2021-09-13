#include "material.h"

class MaterialRefractive : public Material {
public:
    explicit MaterialRefractive(float refractionIndex);

    [[nodiscard]] bool scatter(ScatterRecord &scatterRecord, const Ray &ray, const glm::vec3 &pos,
                               const glm::vec3 &normal, const glm::vec2 &uv, bool frontFace) const override;

private:
    float refractionIndex;

};
