#include "renderer.h"
#include "utils/utils.h"
#include "settings.h"
#include "pdf/pdf_hittable.h"
#include "pdf/pdf_mixture.h"

glm::vec3 calculateRayColor(const Ray &ray, const glm::vec3 &backgroundColor, const Hittable &objects,
                            const std::shared_ptr<HittableList> &lights, uint16_t depth) {
    if (depth >= Settings::MAX_DEPTH)
        return {0.0f, 0.0f, 0.0f};

    HitRecord record = {};

    if (!objects.hit(ray, 0.001, INFINITY, record))
        return backgroundColor;

    glm::vec3 emission = record.materialPtr->emitted(ray, record.pos, record.uv, record.frontFace);

    ScatterRecord scatterRecord = {};
    if (!record.materialPtr->scatter(scatterRecord, ray, record.pos, record.normal, record.uv, record.frontFace))
        return emission;

    if (scatterRecord.isSpecular) {
        return scatterRecord.attenuation *
               calculateRayColor(scatterRecord.specularRay, backgroundColor, objects, lights, depth + 1);
    }

    const auto lightPdf = lights == nullptr ? scatterRecord.pdf : std::make_shared<PdfHittable>(lights, record.pos);
    PdfMixture mixturePdf(lightPdf, scatterRecord.pdf);

    Ray scatteredRay = Ray(record.pos, mixturePdf.generate());

    float pdfRatio = record.materialPtr->scatteringPdf(ray, record.normal, scatteredRay) /
                     mixturePdf.value(scatteredRay.getDirection());

    return emission + scatterRecord.attenuation * pdfRatio
                      * calculateRayColor(scatteredRay, backgroundColor, objects, lights, depth + 1);
}

void writeColor(uint16_t x, uint16_t y, glm::vec3 color, unsigned char* pixels) {
    color = glm::sqrt(color);
    color = glm::clamp(color, 0.0f, 1.0f);
    color *= 0xFF;

    int index = (y * Settings::WIDTH + x) * 3;

    pixels[index + 0] = static_cast<unsigned char>(color.x);
    pixels[index + 1] = static_cast<unsigned char>(color.y);
    pixels[index + 2] = static_cast<unsigned char>(color.z);
}

void renderThreadFunction(const ThreadInfo &threadInfo) {
    uint16_t y = (*threadInfo.nextPixelRowToRender)++;

    while (y < Settings::HEIGHT) {
        for (uint16_t x = 0; x < Settings::WIDTH; x++) {
            float u = (float(x) + randomFloat()) / Settings::WIDTH;
            float v = (float(y) + randomFloat()) / Settings::HEIGHT;

            glm::vec3 calculatedColor =
                    calculateRayColor(threadInfo.scene.getCamera().getRay(u, v), threadInfo.scene.getBackgroundColor(),
                                      threadInfo.scene.getObjects(), threadInfo.scene.getLights(), 0);

            // if x / y / z is NaN, replace it by 0.0f
            if (calculatedColor.x != calculatedColor.x) calculatedColor.x = 0.0f;
            if (calculatedColor.y != calculatedColor.y) calculatedColor.y = 0.0f;
            if (calculatedColor.z != calculatedColor.z) calculatedColor.z = 0.0f;

            threadInfo.summedSampleDataPerPixel[y * Settings::WIDTH + x] += calculatedColor;

            glm::vec3 pixelColor = threadInfo.summedSampleDataPerPixel[y * Settings::WIDTH + x] /
                                   float(*threadInfo.currentPixelSample);

            writeColor(x, y, pixelColor, threadInfo.pixels);
        }

        y = (*threadInfo.nextPixelRowToRender)++;
    }
}
