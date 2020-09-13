#pragma once

namespace Math
{
	class Vector3
	{
	public:
		constexpr Vector3()
			: x(0), y(0), z(0)
		{
		}

		constexpr explicit Vector3(float n)
			: x(n), y(n), z(n)
		{
		}

		constexpr explicit Vector3(const float* af)
			: x(af[0]), y(af[1]), z(af[2])
		{
		}

		constexpr Vector3(float xValue, float yValue, float zValue)
			: x(xValue), y(yValue), z(zValue)
		{
		}

		constexpr Vector3 operator - () const {
			return Vector3(-x, -y, -z);
		}

		constexpr Vector3 operator + (float value) const {
			return Vector3(x + value, y + value, z + value);
		}

		constexpr Vector3 operator + (const Vector3& other) const {
			return Vector3(x + other.x, y + other.y, z + other.z);
		}

		constexpr Vector3 operator - (float value) const {
			return Vector3(x - value, y - value, z - value);
		}

		constexpr Vector3 operator - (const Vector3& other) const {
			return Vector3(x - other.x, y - other.y, z - other.z);
		}

		constexpr Vector3 operator * (float value) const {
			return Vector3(x * value, y * value, z * value);
		}

		constexpr Vector3 operator * (const Vector3& other) const {
			return Vector3(x * other.x, y * other.y, z * other.z);
		}

		Vector3 operator / (float value) const;

		Vector3 operator / (const Vector3& other) const;

		Vector3& operator += (float value) {
			x += value;
			y += value;
			z += value;
			return *this;
		}

		Vector3& operator += (const Vector3& other) {
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		Vector3& operator -= (float value) {
			x -= value;
			y -= value;
			z -= value;
			return *this;
		}

		Vector3& operator -= (const Vector3& other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		Vector3& operator *= (float value) {
			x *= value;
			y *= value;
			z *= value;
			return *this;
		}

		Vector3& operator *= (const Vector3& other) {
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;
		}

		Vector3& operator /= (float value);

		Vector3& operator /= (const Vector3& other);

		constexpr bool operator < (const Vector3& other) const {
			return x < other.x&& y < other.y&& z < other.z;
		}

		constexpr bool operator <= (const Vector3& other) const {
			return x <= other.x && y <= other.y && z <= other.z;
		}

		constexpr bool operator > (const Vector3& other) const {
			return x > other.x && y > other.y && z > other.z;
		}

		constexpr bool operator >= (const Vector3& other) const {
			return x >= other.x && y >= other.y && z >= other.z;
		}

		constexpr bool operator == (const Vector3& other) const {
			return Equals(other);
		}

		constexpr bool operator != (const Vector3& other) const {
			return !Equals(other);
		}
		
		/// Провіряє, чи дорівнює вектор вказанному
		constexpr bool Equals(const Vector3& other, float delta = 0.00001f) const {
			return IsEqualFloat(x, other.x, delta) &&
				IsEqualFloat(y, other.y, delta) &&
				IsEqualFloat(z, other.z, delta);
		}

		// Вертає довжину вектора
		float Length() const;
		
	private:
		// Порівнює два числа на приблизну рівність
		constexpr bool IsEqualFloat(float float1, float float2, float delta = 0.00001f) {
			return (float1 + delta >= float2) && (float1 - delta <= float2);
		}

	public:
		struct {
			float x;
			float y;
			float z;
		};

		// Нульовий вектор
		static const Vector3 Zero;

		// Одиничний вектор
		static const Vector3 One;
	};
}

