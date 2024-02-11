#include "vector2D.h"
#include <cmath>


Vec2::Vec2()
{}

Vec2::Vec2(float xin, float yin)
{
    x = xin;
    y = yin;
}

bool Vec2::operator==(const Vec2& other) const
{
    if (x == other.x && y == other.y)
    {
        return true;
    } else
    {
        return false;
    }
}

bool Vec2::operator!=(const Vec2& other) const
{
    return !(*this == other);
}

Vec2 Vec2::operator-(const Vec2& other) const
{
    return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator/(const Vec2& other) const
{
    return Vec2(x / other.x, y / other.y);
}

Vec2 Vec2::operator*(const Vec2& other) const
{
    return Vec2(x * other.x, y * other.y);
}

Vec2 Vec2::operator+(const Vec2& other) const
{
    return Vec2(x + other.x, y + other.y);
}


void Vec2::operator-=(const Vec2& other)
{
    x = x - other.x;
    y = y - other.y;
}

void Vec2::operator/=(const Vec2& other)
{
    x = x / other.x;
    y = y / other.y;
}

void Vec2::operator*=(const Vec2& other)
{
    x = x * other.x;
    y = y * other.y;
}

void Vec2::operator+=(const Vec2& other)
{
    x = x + other.x;
    y = y + other.y;
}

float Vec2::dist(const Vec2& other) const
{
    return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}

void Vec2::normalize()
{
    float length = sqrt(x * x + y * y);
    if (length != 0)
    {
        x = x / length;
        y = y / length;
    }
}

Vec2 Vec2::operator*(const float& other)
{
    return Vec2(x * other, y * other);
}

