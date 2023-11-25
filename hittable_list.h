#pragma once

#include <memory>
#include <vector>

#include "hittable.h"

class hittable_list : public hittable {
public:
	std::vector<std::shared_ptr<hittable>> objects;

public:
	hittable_list() {}
	hittable_list(std::shared_ptr<hittable> obj) { add(obj); }

	void clear() { objects.clear(); }
	void add(std::shared_ptr<hittable> obj) { objects.push_back(obj); }

	virtual bool hit(const ray& r, float t_min, float t_max, rayhit& rec) const override;
};

bool hittable_list::hit(const ray& r, float t_min, float t_max, rayhit& rec) const {
	rayhit hit;
	bool hasHit = false;
	float closest = t_max;

	for (const auto& obj : objects) {
		if (obj->hit(r, t_min, closest, hit)) {
			hasHit = true;
			closest = hit.t;
			rec = hit;
		}
	}

	return hasHit;
}