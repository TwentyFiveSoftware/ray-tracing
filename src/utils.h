#pragma once

#include "vec3.h"

float randomFloat();

vec3 getRandomUnitVector();

bool isNearZero(const vec3 &vector);

vec3 reflect(const vec3 &vector, const vec3 &normal);

vec3 refract(const vec3 &vector, const vec3 &normal, float refractionRatio);

vec3 getRandomColor();
