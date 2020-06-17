/*
 * Vector2.cpp
 *
 *  Created on: 8 Mar 2014
 *      Author: Khalid
 */

#include "Vector2.h"

#include <math.h>

// For M_PI
#include "SDL2/SDL.h"

// INTEGER TYPE
Vector2::Vector2()
{
	this->x = 0;
	this->y = 0;
}

Vector2::Vector2(Vector2f in)
{
	this->x = (int)float(in.x + 0.5);
	this->y = (int)float(in.y + 0.5);
}


Vector2::Vector2(float x, float y)
{
	this->x = int(floor(x)+0.5);
	this->y = int(floor(y)+0.5);
}

Vector2::Vector2(int x, int y)
{
	this->x = x;
 	this->y = y;
}

float Vector2::Magnitude()
{
	return (float)sqrt(pow(x,2)+pow(y,2));
}

Vector2f Vector2::Normalize()
{
    float magnitude = Magnitude();
    if (magnitude == 0.0f)
        return Vector2(0, 0);

    Vector2f result;
    result.x = x / magnitude;
    result.y = y / magnitude;
    return result;
}

Vector2f Vector2::Rotate(Vector2 point, double degrees)
{
	double rads = degrees*(M_PI/180);
	Vector2f out;
	out.x = (float)(point.x + ((x-point.x)*cos(rads) - (y-point.y)*sin(rads)));
	out.y = (float)(point.y + ((x-point.x)*sin(rads) + (y-point.y)*cos(rads)));
	return out;
}

Vector2 Vector2::operator+(const Vector2& right)
{
    Vector2 result;
    result.x = x + right.x;
    result.y = y + right.y;
    return result;
}
Vector2 Vector2::operator-(const Vector2& right)
{
    Vector2 result;
    result.x = x - right.x;
    result.y = y - right.y;
    return result;
}
Vector2 Vector2::operator-()
{
    return Vector2(0, 0)-(*this);
}

Vector2 Vector2::operator*(const int& right)
{
    Vector2 result;
    result.x = x * right;
    result.y = y * right;
    return result;
}

bool Vector2::operator==(const Vector2& right)
{
    if(x == right.x
	&& y == right.y)
	{
		return true;
	}
    return false;
}

Vector2f Vector2::ToFloat()
{
	return Vector2f(x, y);
}

// FLOAT

Vector2f::Vector2f(void)
{
	x = 0.0f;
	y = 0.0f;
}


Vector2f::Vector2f(Vector2 in)
{
	x = (float)in.x;
	y = (float)in.y;
}

Vector2f::Vector2f(float x, float y)
{
	Vector2f::x = x;
	Vector2f::y = y;
}

Vector2f::Vector2f(int x, int y)
{
	Vector2f::x = (float)x;
 	Vector2f::y = (float)y;
}

float Vector2f::Magnitude()
{
	return (float)sqrt(pow(x,2)+pow(y,2));
}

Vector2f Vector2f::Normalize()
{
    float magnitude = Magnitude();
    if (magnitude == 0.0f)
        return Vector2f(0.0f, 0.0f);

	Vector2f result;
    result.x = x / magnitude;
	result.y = y / magnitude;
    return result;
}

Vector2f Vector2f::Rotate(Vector2f point, double degrees)
{
	double rads = degrees*(M_PI/180);
	Vector2f out;
	out.x = (float)(point.x + ((x-point.x)*cos(rads) - (y-point.y)*sin(rads)));
	out.y = (float)(point.y + ((x-point.x)*sin(rads) + (y-point.y)*cos(rads)));
	return out;
}

Vector2f Vector2f::operator+(const Vector2f& right)
{
    Vector2f result;
    result.x = x + right.x;
    result.y = y + right.y;
    return result;
}
Vector2f Vector2f::operator-(const Vector2f& right)
{
    Vector2f result;
    result.x = x - right.x;
    result.y = y - right.y;
    return result;
}
Vector2f Vector2f::operator-()
{
    return Vector2f(0.f, 0.f)-(*this);;
}

Vector2f Vector2f::operator*(const float& right)
{
    Vector2f result;
    result.x = x * right;
    result.y = y * right;
    return result;
}
Vector2f Vector2f::operator/(const float& right)
{
    Vector2f result;
    result.x = x / right;
    result.y = y / right;
    return result;
}

bool Vector2f::operator==(const Vector2f& right)
{
    if(x == right.x
	&& y == right.y)
	{
		return true;
	}
    return false;
}

Vector2 Vector2f::ToInteger()
{
	return Vector2(	int(floor(x+0.5)),
					int(floor(y+0.5)));
}
