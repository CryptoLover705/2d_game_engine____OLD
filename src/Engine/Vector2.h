/*
 * Vector2.h
 *
 *  Created on: 8 Mar 2014
 *      Author: Khalid
 */
#pragma once

class Vector2f;

class Vector2
{
public:
	Vector2();
	Vector2(int x, int y);
	Vector2(Vector2f in);
	Vector2(float x, float y);
	float Magnitude();
	Vector2f Normalize();
	Vector2f Rotate(Vector2 point, double degrees);
public:
	Vector2 operator+(const Vector2& right);
	Vector2 operator-(const Vector2& right);
	Vector2 operator-();
	Vector2 operator*(const int& right);
	bool operator==(const Vector2& right);

public:
	int x;
	int y;
	Vector2f ToFloat();
};

class Vector2f
{
public:
	Vector2f();
	Vector2f(int x, int y);
	Vector2f(Vector2 in);
	Vector2f(float x, float y);
	float Magnitude();
	Vector2f Normalize();
	Vector2f Rotate(Vector2f point, double degrees);
public:
	Vector2f operator+(const Vector2f& right);
	Vector2f operator-(const Vector2f& right);
	Vector2f operator-();
	Vector2f operator*(const float& right);
	Vector2f operator/(const float& right);
	bool operator==(const Vector2f& right);

public:
	float x;
	float y;
	Vector2 ToInteger();
};
