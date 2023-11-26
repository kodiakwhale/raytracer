#pragma once

#include "constants.h"
#include "color.h"
#include "hittable.h"

class camera {
private:
	int renderWidth = 1600;
	int renderHeight = 900;
	float aspectRatio = static_cast<float>(renderWidth) / static_cast<float>(renderHeight);
	float3 origin;
	float3 corner;
	float3 du;
	float3 dv;

private:
	void init() {
		origin = float3();
		float focalLength = 1;
		float viewportHeight = 2;
		float viewportWidth = viewportHeight * aspectRatio;

		float3 vu = float3(viewportWidth, 0, 0);
		float3 vv = float3(0, viewportHeight, 0);

		du = vu / renderWidth;
		dv = vv / renderHeight;

		float3 upper_left = origin - float3(0, 0, focalLength) - vu / 2 - vv / 2;
		corner = upper_left + (du + dv) * 0.5;
	}
	
	float3 trace(const ray& r, const hittable& world) const {
		rayhit hit;
		if (world.hit(r, interval(0, inf), hit)) {
			return (hit.normal + float3(1.0, 0.2, 1.0)) * 0.5;
		}
		float t = (r.dir.normalized().y + 1) * 0.5;
		return float3(0.8, 0.7, 1) * (1 - t) + float3(0.2, 0.1, 0.6) * t;
	}

public:
	
	void render(const hittable& world) {
		init();

		std::cout << "P3\n" << renderWidth << ' ' << renderHeight << "\n255\n";

		for (int j = renderHeight - 1; j >= 0; j--) {
			std::cerr << "\rLines remaining: " << j << '/' << renderHeight << ' ' << std::flush;
			for (int i = 0; i < renderWidth; i++) {
				float3 pixelCenter = corner + (du * i) + (dv * j);
				float3 dir = pixelCenter - origin;
				float3 pixel = trace(ray(origin, dir), world);
				write_color(std::cout, pixel);
			}
		}
		std::cerr << "\nFinished!\n";
	}
};