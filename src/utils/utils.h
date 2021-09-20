#pragma once

#include <glm/glm.hpp>
#include "../aabb.h"

const float PI = 3.1415926535897932385f;

float degreesToRadians(float degrees);

float randomFloat(float min, float max);

float randomFloat();

int32_t randomInt(int32_t min, int32_t max);

glm::vec3 randomVector(float min, float max);

glm::vec3 getRandomPointInUnitSphere();

glm::vec3 getRandomUnitVector();

bool isVectorNearZero(const glm::vec3 &vector);

glm::vec3 reflectVector(const glm::vec3 &vector, const glm::vec3 &normal);

glm::vec3 refractVector(const glm::vec3 &vector, const glm::vec3 &normal, float refractiveIndexRatio);

bool canRefract(const glm::vec3 &vector, const glm::vec3 &normal, float refractiveIndexRatio);

float reflectanceFactorApproximation(const glm::vec3 &vector, const glm::vec3 &normal, float refractionIndexRatio);

glm::vec3 getRandomPointInUnitDisk();

AABB calculateSurroundingBox(AABB box1, AABB box2);

glm::vec3 randomToSphere(float radius, float distance);

glm::vec3 getRandomColor();
