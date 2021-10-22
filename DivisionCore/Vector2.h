#pragma once

#include <cmath>

using namespace std;

namespace DivisionCore { namespace Vectors
{
    struct Vector2
    {
    public:
        float x{}, y{};
        Vector2() = default;
        Vector2(const float& _x, const float& _y)
        {
            x = _x;
            y = _y;
        }
        Vector2(const Vector2& from, const Vector2& to)
        {
            Vector2 temp = from - to;

            x = temp.x;
            y = temp.y;
        }

        static inline Vector2 Zero()
        {
            return Vector2{0, 0};
        }
        static inline Vector2 One()
        {
            return Vector2{1, 1};
        }
        static inline Vector2 Up()
        {
            return Vector2{0, 1};
        }
        static inline Vector2 Down()
        {
            return Vector2{0, -1};
        }
        static inline Vector2 Left()
        {
            return Vector2{-1, 0};
        }
        static inline Vector2 Right()
        {
            return Vector2{1, 0};
        }
        
        inline Vector2 operator + (const Vector2& other) const
        {
            return Vector2{other.x + x, other.y + y};
        }
        inline Vector2 operator - (const Vector2& other) const
        {
            return Vector2{x - other.x, y - other.y};
        }
        inline Vector2 operator * (const float& other) const
        {
            return Vector2{x * other, y * other};
        }
        
        inline bool operator == (const Vector2& other) const
        {
            return x == other.x && y == other.y;
        }
        inline bool operator != (const Vector2& other) const
        {
            return x != other.x && y != other.y;
        }
        
        inline float Magnitude() const
        {
            return sqrtf(powf(x, 2) + powf(y, 2));
        }
        inline Vector2 Normalized() const
        {
            return Vector2{x > 0 ? x / Magnitude() : 0, y > 0 ? y / Magnitude() : 0};
        }
        inline Vector2 OverrideNormalized()
        {
            x = x > 0 ? x / Magnitude() : 0;
            y = y > 0 ? y / Magnitude() : 0;
            
            return *this;
        }
    };
} }
