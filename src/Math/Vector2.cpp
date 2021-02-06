#pragma once

#include <iostream>
#include "Vector2.h"

namespace Math 
{
	const Vector2 Vector2::Zero(0, 0);
	const Vector2 Vector2::One(1, 1);

	Vector2 Vector2::operator / (float value) const {
		float valueInv = 1.0f / value;
		return Vector2(x * valueInv, y * valueInv);
	}

	Vector2 Vector2::operator / (const Vector2& other) const {
		return Vector2(x / other.x, y / other.y);
	}

	Vector2& Vector2::operator /= (float value) {
		float valueInv = 1.0f / value;
		x *= valueInv;
		y *= valueInv;
		return *this;
	}

	Vector2& Vector2::operator /= (const Vector2& other) {
		x /= other.x;
		y /= other.y;
		return *this;
	}

	float Vector2::Length() const {
		return std::sqrt(x * x + y * y);
	}
}