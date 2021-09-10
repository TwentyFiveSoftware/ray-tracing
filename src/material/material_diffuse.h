#include "material.h"

class MaterialDiffuse : public Material {
public:
    MaterialDiffuse(const glm::vec3 &albedo);

    [[nodiscard]] ScatterInfo scatter(const Ray &ray, const glm::vec3 &pos, const glm::vec3 &normal) const override;

private:
    glm::vec3 albedo;

};
