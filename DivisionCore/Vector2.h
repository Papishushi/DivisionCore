/**
  * @file Vector2.h
  * @author Daniel Molinero Lucas (Papishushi)
  * @section Copyright © <2021+> <Daniel Molinero Lucas (Papishushi)> MIT LICENSE
  * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
  * to deal in the Software without restriction, including without limitation the rights to use, copy,
  * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
  * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
  *
  * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
  * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
  **/
#ifndef DIVISIONCORE_VECTOR2_H
#define DIVISIONCORE_VECTOR2_H

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
#endif //DIVISIONCORE_VECTOR2_H
