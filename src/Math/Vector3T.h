#pragma once

#include "Vector2.h"

namespace Math
{
	class Vector3T : public Vector2
	{
	public:
		constexpr Vector3T()
			: Vector2(0, 0), z(0)
		{
		}

		constexpr explicit Vector3T(float n)
			: Vector2(n, n), z(n)
		{
		}

		constexpr explicit Vector3T(const float* af)
			: Vector2(af[0], af[1]), z(af[2])
		{
		}

		constexpr Vector3T(float xValue, float yValue, float zValue)
			: Vector2(xValue, yValue), z(zValue)
		{
		}

		constexpr explicit Vector3T(Vector2& vec2)
			: Vector2(vec2.x, vec2.y), z(0)
		{
		}

		constexpr Vector3T operator - () const {
			return Vector3T(-x, -y, -z);
		}

		constexpr Vector3T operator + (float value) const {
			return Vector3T(x + value, y + value, z + value);
		}

		constexpr Vector3T operator + (const Vector3T& other) const {
			return Vector3T(x + other.x, y + other.y, z + other.z);
		}

		constexpr Vector3T operator - (float value) const {
			return Vector3T(x - value, y - value, z - value);
		}

		constexpr Vector3T operator - (const Vector3T& other) const {
			return Vector3T(x - other.x, y - other.y, z - other.z);
		}

		constexpr Vector3T operator * (float value) const {
			return Vector3T(x * value, y * value, z * value);
		}

		constexpr Vector3T operator * (const Vector3T& other) const {
			return Vector3T(x * other.x, y * other.y, z * other.z);
		}

		Vector3T operator / (float value) const;

		Vector3T operator / (const Vector3T& other) const;

		Vector3T& operator += (float value) {
			Vector2::operator+=(value);
			z += value;
			return *this;
		}

		Vector3T& operator += (const Vector3T& other) {
			Vector2::operator+=(Vector2(other.x, other.y));
			z += other.z;
			return *this;
		}

		Vector3T& operator -= (float value) {
			Vector2::operator-=(value);
			z -= value;
			return *this;
		}

		Vector3T& operator -= (const Vector3T& other) {
			Vector2::operator-=(Vector2(other.x, other.y));
			z -= other.z;
			return *this;
		}

		Vector3T& operator *= (float value) {
			Vector2::operator*=(value);
			z *= value;
			return *this;
		}

		Vector3T& operator *= (const Vector3T& other) {
			Vector2::operator*=(Vector2(other.x, other.y));
			z *= other.z;
			return *this;
		}

		Vector3T& operator /= (float value);

		Vector3T& operator /= (const Vector3T& other);

		constexpr bool operator < (const Vector3T& other) const {
			return Vector2::operator<(Vector2(other.x, other.y)) && z < other.z;
		}

		constexpr bool operator <= (const Vector3T& other) const {
			return Vector2::operator<=(Vector2(other.x, other.y)) && z <= other.z;
		}

		constexpr bool operator > (const Vector3T& other) const {
			return Vector2::operator>(Vector2(other.x, other.y)) && z > other.z;
		}

		constexpr bool operator >= (const Vector3T& other) const {
			return Vector2::operator>=(Vector2(other.x, other.y)) && z >= other.z;
		}

		constexpr bool operator == (const Vector3T& other) const {
			return Equals3(other);
		}

		constexpr bool operator != (const Vector3T& other) const {
			return !Equals3(other);
		}

		/// Провіряє, чи дорівнює вектор вказанному
		constexpr bool Equals3(const Vector3T& other, float delta = 0.00001f) const {
			return Equals(Vector2(other.x, other.y), delta) &&
				IsEqualFloat(z, other.z, delta);
		}

		// Вертає довжину вектора
		float Length() const;

	public:
		float z;

		// Нульовий вектор
		static const Vector3T Zero;

		// Одиничний вектор
		static const Vector3T One;
	};
}

