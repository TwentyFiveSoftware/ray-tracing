#pragma once

#include <glm/glm.hpp>

float randomFloat(float min, float max);

float randomFloat();

glm::vec3 randomVector(float min, float max);

glm::vec3 getRandomPointInUnitSphere();

glm::vec3 getRandomUnitVector();

bool isVectorNearZero(const glm::vec3 &vector);

glm::vec3 reflectVector(const glm::vec3 &vector, const glm::vec3 &normal);
