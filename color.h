#pragma once

#include <iostream>

#include "float3.h"

void write_color(std::ostream& out, const float3& color) {
	out << static_cast<int>(256 * color.x) << ' '
		<< static_cast<int>(256 * color.y) << ' '
		<< static_cast<int>(256 * color.z) << '\n';
}