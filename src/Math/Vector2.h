#pragma once

namespace Math
{
	class Vector2
	{
	public:
		constexpr Vector2()
			: x(0), y(0)
		{
		}

		constexpr explicit Vector2(float n)
			: x(n), y(n)
		{
		}

		constexpr explicit Vector2(const float* af)
			: x(af[0]), y(af[1])
		{
		}

		constexpr Vector2(float xValue, float yValue)
			: x(xValue), y(yValue)
		{
		}

		constexpr Vector2 operator - () const {
			return Vector2(-x, -y);
		}

		constexpr Vector2 operator + (float value) const {
			return Vector2(x + value, y + value);
		}

		constexpr Vector2 operator + (const Vector2& other) const {
			return Vector2(x + other.x, y + other.y);
		}

		constexpr Vector2 operator - (float value) const {
			return Vector2(x - value, y - value);
		}

		constexpr Vector2 operator - (const Vector2& other) const {
			return Vector2(x - other.x, y - other.y);
		}

		constexpr Vector2 operator * (float value) const {
			return Vector2(x * value, y * value);
		}

		constexpr Vector2 operator * (const Vector2& other) const {
			return Vector2(x * other.x, y * other.y);
		}

		Vector2 operator / (float value) const;

		Vector2 operator / (const Vector2& other) const;

		Vector2& operator += (float value) {
			x += value;
			y += value;
			return *this;
		}

		Vector2& operator += (const Vector2& other) {
			x += other.x;
			y += other.y;
			return *this;
		}

		Vector2& operator -= (float value) {
			x -= value;
			y -= value;
			return *this;
		}

		Vector2& operator -= (const Vector2& other) {
			x -= other.x;
			y -= other.y;
			return *this;
		}

		Vector2& operator *= (float value) {
			x *= value;
			y *= value;
			return *this;
		}

		Vector2& operator *= (const Vector2& other) {
			x *= other.x;
			y *= other.y;
			return *this;
		}

		Vector2& operator /= (float value);

		Vector2& operator /= (const Vector2& other);

		constexpr bool operator < (const Vector2& other) const {
			return x < other.x&& y < other.y;
		}

		constexpr bool operator <= (const Vector2& other) const {
			return x <= other.x && y <= other.y;
		}

		constexpr bool operator > (const Vector2& other) const {
			return x > other.x && y > other.y;
		}

		constexpr bool operator >= (const Vector2& other) const {
			return x >= other.x && y >= other.y;
		}

		constexpr bool operator == (const Vector2& other) const {
			return Equals(other);
		}

		constexpr bool operator != (const Vector2& other) const {
			return !Equals(other);
		}
		
		/// Провіряє, чи дорівнює вектор вказанному
		constexpr bool Equals(const Vector2& other, float delta = 0.00001f) const {
			return IsEqualFloat(x, other.x, delta) &&
				IsEqualFloat(y, other.y, delta);
		}

		// Вертає довжину вектора
		float Length() const;
		
	protected:
		// Порівнює два числа на приблизну рівність
		constexpr bool IsEqualFloat(float float1, float float2, float delta = 0.00001f) const {
			return (float1 + delta >= float2) && (float1 - delta <= float2);
		}

	public:
		float x;
		float y;

		// Нульовий вектор
		static const Vector2 Zero;

		// Одиничний вектор
		static const Vector2 One;
	};
}

