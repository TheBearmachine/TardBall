#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>


class Vector
{
public:
	float x, y;

	Vector(const float& x, const float& y)
	{
		Vector::x = x;
		Vector::y = y;
	}

	Vector()
	{
		x = 0.0f;
		y = 0.0f;
	}

	bool isZero() const
	{
		return x == 0 && y == 0;
	}

	float lenght() const
	{
		float pX = powf(x, 2);
		float pY = powf(y, 2);

		return sqrtf(pX + pY);
	}

	Vector normalize() const
	{
		float length = lenght();
		if (length != 0)
			return Vector(x / length, y / length);
		return Vector(0, 0);
	}

	//Convert to sf::vector2f
	sf::Vector2f toVector2f() const
	{
		return sf::Vector2f(x, y);
	}

	//Copy Constructors
	Vector(const Vector& vector)
	{
		x = vector.x;
		y = vector.y;
	}

	explicit Vector(const sf::Vector2f& vector)
	{
		x = vector.x;
		y = vector.y;
	}

	///////////////

	//Operators to sf::Vector
	template <typename T>
	void operator=(sf::Vector2<T> vector)
	{
		x = float(vector.x);
		y = float(vector.y);
	}

	template <typename T>
	Vector operator+(sf::Vector2<T> vector)
	{
		return Vector(x + float(vector.x), y + float(vector.y));
	}

	template <typename T>
	void operator+=(sf::Vector2<T> vector)
	{
		x = x + float(vector.x);
		y = y + float(vector.y);
	}

	template <typename T>
	Vector operator-(sf::Vector2<T> vector)
	{
		return Vector(x - float(vector.x), y - float(vector.y));
	}

	template <typename T>
	void operator-=(sf::Vector2<T> vector)
	{
		x = x - float(vector.x);
		y = y - float(vector.y);
	}

	//Operators from Vector to Vector
	Vector operator-() const
	{
		return Vector(-x, -y);
	}

	Vector operator+(const Vector& vector) const
	{
		return Vector(x + float(vector.x), y + float(vector.y));
	}

	Vector operator-(const Vector& vector) const
	{
		return Vector(x - float(vector.x), y - float(vector.y));
	}

	Vector operator*(const Vector& vector) const
	{
		return Vector(x * vector.x, y * vector.y);
	}

	void operator+=(const Vector& vector)
	{
		x += vector.x;
		y += vector.y;
	}

	void operator-=(const Vector& vector)
	{
		x -= vector.x;
		y -= vector.y;
	}

	//Vector and float
	Vector operator*(const float& f) const
	{
		return Vector(x * f, y * f);
	}

	void operator*=(const float& f)
	{
		x = x * f;
		y = y * f;
	}

	void operator-=(const float& f)
	{
		x = x - f;
		y = y - f;
	}

	Vector operator/(const float& f) const
	{
		return Vector(x / f, y / f);
	}

	void operator/=(const float& f)
	{
		x = x / f;
		y = y / f;
	}


	bool operator!=(Vector vector) const
	{
		if (x == vector.x && y == vector.y)
			return false;

		return true;
	}
};
