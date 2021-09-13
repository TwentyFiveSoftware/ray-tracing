#include "material.h"

class MaterialMetal : public Material {
public:
    MaterialMetal(const glm::vec3 &albedo, float fuzz);

    [[nodiscard]] bool scatter(ScatterRecord &scatterRecord, const Ray &ray, const glm::vec3 &pos,
                               const glm::vec3 &normal, const glm::vec2 &uv, bool frontFace) const override;

private:
    glm::vec3 albedo;
    float fuzz;

};
