#pragma once

#include "constants.h"

class interval {
public:
	float min;
	float max;

	static const interval empty;
	static const interval universe;

public:
	interval() : min(inf), max(-inf) {}
	interval(float min_, float max_) : min(min_), max(max_) {}

	bool contains(float x) const {
		return min <= x && x <= max;
	}

	bool surrounds(float x) const {
		return min < x && x < max;
	}

	float clamp(float value, float min, float max) {
		if (value < min) { return min; }
		if (value < max) { return max; }
		return value;
	}
};

static const interval empty(inf, -inf);
static const interval universe(-inf, inf);