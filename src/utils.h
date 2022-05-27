#pragma once

#include <random>

float randomFloat(float min, float max);

float randomFloat();

glm::vec3 getRandomUnitVector();

bool isNearZero(const glm::vec3 &vector);
