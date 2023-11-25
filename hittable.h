#pragma once

#include "ray.h"

struct rayhit {
	float3 point;
	float3 normal;
	float t;
	bool front;

	inline void SetFront(const ray& r, const float3& outNormal) {
		front = dot(r.dir, normal) < 0;
		normal = front ? outNormal : -outNormal;
	}
};

class hittable {
public:
	virtual bool hit(const ray& r, float t_min, float t_max, rayhit& rec) const = 0;
};