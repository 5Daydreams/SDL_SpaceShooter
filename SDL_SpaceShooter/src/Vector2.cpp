#include "Vector2.h"

const Vector2 Vector2::Zero = Vector2(0.0f, 0.0f);
const Vector2 Vector2::One = Vector2(1.0f, 1.0f);
const Vector2 Vector2::Forward = Vector2(0.0f, 1.0f);
const Vector2 Vector2::Right = Vector2(1.0f, 0.0f);

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

float Vector2::Magnitude() const
{
	float magSquared = (this->x) * (this->x) + (this->y) * (this->y);
	float vecSize = sqrt(magSquared);
	return vecSize;
}

Vector2& Vector2::Normalize()
{
	float vecSize = this->Magnitude();

	if (this->Magnitude() < 0.00001f)
	{
		vecSize = 1.0f;
	}

	this->x /= vecSize;
	this->y /= vecSize;

	return *this;
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

Vector2 operator*(const float scalar, const Vector2& v1)
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
Vector2& Vector2::Rotate(const float radians)
{
	*this = Vector2(
		cos(radians) * this->x - sin(radians) * this->y,
		sin(radians) * this->x + cos(radians) * this->y
	);

	return *this;
}

Vector2& Vector2::ClampMagnitude(const float scalar)
{
	if(scalar < 0.f)
	{
		return *this;
	}

	const float vecSize = this->Magnitude();

	if(vecSize > scalar)
	{
		this->Normalize();

		this->x *= scalar;
		this->y *= scalar;
	}

	return *this;
}