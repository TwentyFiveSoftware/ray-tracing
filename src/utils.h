#pragma once

#include <random>

float randomFloat();

glm::vec3 getRandomUnitVector();

bool isNearZero(const glm::vec3 &vector);

glm::vec3 reflect(const glm::vec3 &vector, const glm::vec3 &normal);

glm::vec3 refract(const glm::vec3 &vector, const glm::vec3 &normal, float refractionRatio);

glm::vec3 getRandomColor();
