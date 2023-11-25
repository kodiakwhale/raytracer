#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

constexpr float inf = std::numeric_limits<float>::infinity();
constexpr float pi = 3.1415926535897932385;

inline float DegToRad(float degrees) {
	return degrees * pi / 180.0;
}

inline float random() {
	return rand() / (RAND_MAX + 1.0);
}

inline float random(float min, float max) {
	return min + (max - min) * random();
}