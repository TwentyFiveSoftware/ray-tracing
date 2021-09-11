#include "material.h"

class MaterialMetal : public Material {
public:
    MaterialMetal(const glm::vec3 &albedo, float fuzz);

    [[nodiscard]] ScatterInfo scatter(const Ray &ray, const glm::vec3 &pos, const glm::vec3 &normal,
                                      bool frontFace) const override;

private:
    glm::vec3 albedo;
    float fuzz;

};
