#include <iostream>
#include <optional>

#include "color.h"
#include "hittable_list.h"
#include "constants.h"
#include "sphere.h"

float3 Hit(const ray& r, const hittable& world) {
    rayhit hit;
    if (world.hit(r, 0, inf, hit)) {
        return (hit.normal + float3(1.0, 0.2, 1.0)) * 0.5;
    }
    float t = (r.dir.normalized().y + 1) * 0.5;
    return float3(0.8, 0.7, 1) * (1 - t) + float3(0.2, 0.1, 0.6) * t;
}

int main() {

    // Image
    constexpr int renderWidth = 1600;
    constexpr int renderHeight = 900;
    constexpr float aspectRatio = static_cast<float>(renderWidth) / static_cast<float>(renderHeight);

    // World
    hittable_list world;
    world.add(std::make_shared<sphere>(float3(0, 0, -1), 0.5));
    world.add(std::make_shared<sphere>(float3(0, -50.5, -1), 50));

    // Camera
    constexpr float viewportHeight = 2.0;
    constexpr float viewportWidth = viewportHeight * aspectRatio;
    constexpr float focalLength = 1.0;

    float3 origin = float3();
    float3 horizontal = float3(viewportWidth, 0, 0);
    float3 vertical = float3(0, viewportHeight, 0);
    float3 corner = origin - horizontal / 2 - vertical / 2 - float3(0, 0, focalLength);

    // Render
    std::cout << "P3\n" << renderWidth << ' ' << renderHeight << "\n255\n";

    for (int j = renderHeight - 1; j >= 0; j--) {
        std::cerr << "\rLines remaining: " << j << '/' << renderHeight << ' ' << std::flush;
        for (int i = 0; i < renderWidth; i++) {
            float u = static_cast<float>(i) / (renderWidth - 1);
            float v = static_cast<float>(j) / (renderHeight - 1);
            ray r(origin, corner + horizontal * u + vertical * v - origin);
            float3 pixel = Hit(r, world);
            write_color(std::cout, pixel);
        }
    }
    std::cerr << "\nFinished!\n";
}
