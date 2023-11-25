#pragma once

#include "float3.h"

class ray {
public:
	float3 origin;
	float3 dir;

public:
	ray() {}
	ray(const float3& origin_, const float3& dir_) : origin{origin_}, dir{dir_} {}

	float3 at(float magnitude) const {
		return origin + dir * magnitude;
	}
};