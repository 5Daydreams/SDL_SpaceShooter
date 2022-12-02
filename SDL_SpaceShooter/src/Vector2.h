#pragma once

#include <iostream>

class Vector2
{
public:
	float x;
	float y;

	Vector2();
	Vector2(float x, float y);

	Vector2& Add(const Vector2& vec);
	friend Vector2 operator+(const Vector2& v1, const Vector2& v2);
	Vector2& operator+=(const Vector2& vec);

	Vector2& Subtract(const Vector2& vec);
	friend Vector2 operator-(const Vector2& v1, const Vector2& v2);
	Vector2& operator-=(const Vector2& vec);

	Vector2& Multiply(const Vector2& vec);
	friend Vector2 operator*(const Vector2& v1, const Vector2& v2);
	Vector2& operator*=(const Vector2& vec);

	Vector2& Divide(const Vector2& vec);
	friend Vector2 operator/(const Vector2& v1, const Vector2& v2);
	Vector2& operator/=(const Vector2& vec);

	Vector2& Multiply(const float scalar);
	friend Vector2 operator*(const Vector2& v1, const float scalar);
	friend Vector2 operator*(const float scalar, const Vector2& v1);
	Vector2& operator*=(const float scalar);

	friend std::ostream& operator<<(std::ostream& stream, const Vector2& vec);

	Vector2& Rotate(const float scalar);

	static const Vector2 Zero;
	static const Vector2 One;
};
