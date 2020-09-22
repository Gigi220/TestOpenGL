#pragma once

#include <iostream>
#include "Vector3T.h"

namespace Math 
{
	const Vector3T Vector3T::Zero(0, 0, 0);
	const Vector3T Vector3T::One(1, 1 ,1);

	Vector3T Vector3T::operator / (float value) const {
		float valueInv = 1.0f / value;
		return Vector3T(x * valueInv, y * valueInv, z * valueInv);
	}

	Vector3T Vector3T::operator / (const Vector3T& other) const {
		return Vector3T(x / other.x, y / other.y, z / other.z);
	}

	Vector3T& Vector3T::operator /= (float value) {
		float valueInv = 1.0f / value;
		Vector2::operator*=(valueInv);
		z *= valueInv;
		return *this;
	}

	Vector3T& Vector3T::operator /= (const Vector3T& other) {
		Vector2::operator/=(Vector2(other.x, other.y));
		z /= other.z;
		return *this;
	}

	float Vector3T::Length() const {
		return std::sqrt(x * x + y * y + z * z);
	}
}