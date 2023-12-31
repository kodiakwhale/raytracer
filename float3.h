#pragma once

#include <iostream>
#include <cmath>
#include "constants.h"

class float3;

float3 operator/(const float3& lhs, float scale);

class float3 {
public:
	float x;
	float y;
	float z;

public:
	float3() : x{0}, y{0}, z{0} {}
	float3(float x_, float y_, float z_) : x{x_}, y{y_}, z{z_} {}

	float3 operator-() const { return float3{-x, -y, -z}; }
	float3& operator+=(const float3& rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;

		return *this;
	}

	float3& operator-=(const float3& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;

		return *this;
	}

	float3& operator*=(float scale) {
		x *= scale;
		y *= scale;
		z *= scale;

		return *this;
	}

	float3& operator/=(float scale) {
		x /= scale;
		y /= scale;
		z /= scale;

		return *this;
	}

	float sqrMagnitude() const {
		return x*x + y*y + z*z;
	}

	float magnitude() const {
		return std::sqrt(sqrMagnitude());
	}

	// Returns float3 with magnitude between -1 and 1
	float3 normalized() const {
		return *this / magnitude();
	}

	static float3 Random() {
		return float3(RandomFloat(), RandomFloat(), RandomFloat());
	}

	static float3 Random(float min, float max) {
		return float3(RandomFloat(min, max), RandomFloat(min, max), RandomFloat(min, max));
	}
};

// TODO: mark following functions as inline?

std::ostream& operator<<(std::ostream& out, const float3& vec) {
	return out << vec.x << ' ' << vec.y << ' ' << vec.z;
}

float3 operator+(const float3& lhs, const float3& rhs) {
	return float3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

float3 operator-(const float3& lhs, const float3& rhs) {
	return float3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

float3 operator*(const float3& lhs, const float3& rhs) {
	return float3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}

float3 operator/(const float3& lhs, const float3& rhs) {
	return float3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
}

float3 operator*(const float3& lhs, float scale) {
	return float3(lhs.x * scale, lhs.y * scale, lhs.z * scale);
}

float3 operator/(const float3& lhs, float scale) {
	return float3(lhs.x / scale, lhs.y / scale, lhs.z / scale);
}

float dot(const float3& lhs, const float3& rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

float3 cross(const float3& lhs, const float3& rhs) {
	return float3(lhs.y * rhs.z - lhs.z * rhs.y,
				  lhs.z * rhs.x - lhs.x * rhs.z,
				  lhs.x * rhs.y - lhs.y * rhs.x);
}

float3 RandomUnitVector() {
	while (true) {
		float3 vec = float3::Random(-1, 1);
		if (vec.sqrMagnitude() >= 1) {
			return vec.normalized();
		}
	}
}

float3 RandomHemisphere(const float3& normal) {
	float3 vec = RandomUnitVector();
	if (dot(vec, normal) < 0.0) {
		return vec;
	} else {
		return -vec;
	}
}
