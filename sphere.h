#pragma once

#include "hittable.h"

class sphere : public hittable {
public:
	float3 center;
	float radius;

public:
	sphere() : radius{0} {}
	sphere(float3 center_, float radius_) : center(center_), radius(radius_) {}

	virtual bool hit(const ray& r, float t_min, float t_max, rayhit& rec) const override;
};

bool sphere::hit(const ray& r, float t_min, float t_max, rayhit& rec) const {
    float3 p = r.origin - center;
    float a = r.dir.sqrMagnitude();
    float h = dot(p, r.dir);
    float c = p.sqrMagnitude() - radius * radius;
    float discrim = h * h - a * c;
    if (discrim < 0) {
        return false;
    }

    float sqrtDiscrim = std::sqrt(discrim);

    float root = (-h - sqrtDiscrim) / a;
    if (root < t_min || t_max < root) {
        root = (-h + sqrtDiscrim) / a;
        if (root < t_min || t_max < root) {
            return false;
        }
    }

    rec.point = r.at(root);
    rec.SetFront(r, (rec.point - center) / radius);
    rec.t = root;

    return true;
}