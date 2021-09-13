#pragma once

#include "../structs/scatter_record.h"

class Material {
public:
    [[nodiscard]] virtual glm::vec3 emitted(const Ray &ray, const glm::vec3 &pos, const glm::vec2 &uv,
                                            bool frontFace) const {
        return {0.0f, 0.0f, 0.0f};
    }

    [[nodiscard]] virtual bool scatter(ScatterRecord &scatterRecord, const Ray &ray, const glm::vec3 &pos,
                                       const glm::vec3 &normal, const glm::vec2 &uv, bool frontFace) const {
        return false;
    }

    [[nodiscard]] virtual float scatteringPdf(const Ray &ray, const glm::vec3 &normal, const Ray &scatteredRay) const {
        return 0.0f;
    }

};
