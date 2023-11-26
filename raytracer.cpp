#include <iostream>
#include <optional>

#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

float3 Hit(const ray& r, const hittable& world) {
    rayhit hit;
    if (world.hit(r, interval(0, inf), hit)) {
        return (hit.normal + float3(1.0, 0.2, 1.0)) * 0.5;
    }
    float t = (r.dir.normalized().y + 1) * 0.5;
    return float3(0.8, 0.7, 1) * (1 - t) + float3(0.2, 0.1, 0.6) * t;
}

int main() {
    // World
    hittable_list world;
    world.add(std::make_shared<sphere>(float3(0, 0, -1), 0.5));
    world.add(std::make_shared<sphere>(float3(0, -50.5, -1), 50));

    camera cam;
    cam.render(world);
}
