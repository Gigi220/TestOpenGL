#pragma once

#include <iostream>
#include "Vector3.h"

namespace Math 
{
	const Vector3 Vector3::Zero(0, 0, 0);
	const Vector3 Vector3::One(1, 1, 1);

	Vector3 Vector3::operator / (float value) const {
		float valueInv = 1.0f / value;
		return Vector3(x * valueInv, y * valueInv, z * valueInv);
	}

	Vector3 Vector3::operator / (const Vector3& other) const {
		return Vector3(x / other.x, y / other.y, z / other.z);
	}

	Vector3& Vector3::operator /= (float value) {
		float valueInv = 1.0f / value;
		x *= valueInv;
		y *= valueInv;
		z *= valueInv;
		return *this;
	}

	Vector3& Vector3::operator /= (const Vector3& other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}

	float Vector3::Length() const {
		return std::sqrt(x * x + y * y + z * z);
	}
}