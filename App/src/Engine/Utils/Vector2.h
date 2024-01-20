#pragma once

namespace MyEngine
{
    class Vec2
    {
    public:
        // Constructors
        Vec2();
        Vec2(float _x, float _y);

        Vec2(const Vec2& other);

        ~Vec2() {}

        Vec2& operator=(const Vec2& other);

        Vec2 operator+(const Vec2& other) const;

        Vec2 operator-(const Vec2& other) const;

        Vec2 operator*(float scalar) const;

        Vec2 operator/(float scalar) const;

        // Unary negation operator
        Vec2 operator-() const;

        float Dot(const Vec2& other) const;

        float Cross(const Vec2& other) const;

        float Length() const;

        Vec2 Normalize() const;

        float x, y;
    };
}
