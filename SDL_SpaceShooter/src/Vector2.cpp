#include "Vector2.h"

static const Vector2 Zero = Vector2(0.0f, 0.0f);
static const Vector2 One = Vector2(1.0f, 1.0f);

Vector2::Vector2()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2& Vector2::Add(const Vector2& vec)
{
	this->x += vec.x;
	this->y += vec.y;
	return *this;
}

Vector2& Vector2::Subtract(const Vector2& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return *this;
}

Vector2& Vector2::Multiply(const Vector2& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;
	return *this;
}

Vector2& Vector2::Divide(const Vector2& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;
	return *this;
}

Vector2 operator+(const Vector2& v1, const Vector2& v2)
{
	Vector2 v3 = Vector2(v1.x + v2.x, v1.y + v2.y);
	return v3;
}

Vector2 operator-(const Vector2& v1, const Vector2& v2)
{
	Vector2 v3 = Vector2(v1.x - v2.x, v1.y - v2.y);
	return v3;
}

Vector2 operator*(const Vector2& v1, const Vector2& v2)
{
	Vector2 v3 = Vector2(v1.x * v2.x, v1.y * v2.y);
	return v3;
}

Vector2 operator/(const Vector2& v1, const Vector2& v2)
{
	Vector2 v3 = Vector2(v1.x / v2.x, v1.y / v2.y);
	return v3;
}

Vector2& Vector2::operator+=(const Vector2& vec)
{
	return this->Add(vec);
}

Vector2& Vector2::operator-=(const Vector2& vec)
{
	return this->Subtract(vec);
}

Vector2& Vector2::operator*=(const Vector2& vec)
{
	return this->Multiply(vec);
}

Vector2& Vector2::operator/=(const Vector2& vec)
{
	return this->Divide(vec);
}

Vector2& Vector2::Multiply(const float scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	return *this;
}

Vector2 operator*(const Vector2& v1, const float scalar)
{
	Vector2 v3 = Vector2(v1.x * scalar, v1.y * scalar);
	return v3;
}

Vector2& Vector2::operator*=(const float scalar)
{
	return this->Multiply(scalar);
}

std::ostream& operator<<(std::ostream& stream, const Vector2& vec)
{
	stream << "(" << vec.x << "," << vec.y << ")";
	return stream;
}
