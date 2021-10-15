#pragma once

#include <iostream>
#include <cmath>

using namespace std;

namespace Gametility
{
    namespace Vectors
    {
        struct Vector2
        {
        public:
            float x;
            float y;

            Vector2(const float _x, const float _y)
            {
                x = _x;
                y = _y;
            }

            inline const Vector2 Zero() const
            {
                return Vector2(0, 0);
            }
            inline const Vector2 One() const
            {
                return Vector2(1, 1);
            }
            inline const Vector2 Up() const
            {
                return Vector2(0, 1);
            }
            inline const Vector2 Down() const
            {
                return Vector2(0, -1);
            }
            inline const Vector2 Left() const
            {
                return Vector2(-1, 0);
            }
            inline const Vector2 Right() const
            {
                return Vector2(1, 0);
            }

            inline Vector2 operator + (const Vector2& other) const
            {
                return Vector2(other.x + x, other.y + y);
            }
            inline Vector2 operator - (const Vector2& other) const
            {
                return Vector2(x - other.x, y - other.y);
            }
            inline Vector2 operator * (const float& other) const
            {
                return Vector2(x * other, y * other);
            }

            inline float Magnitude()
            {
                return sqrtf(powf(x, 2) + powf(y, 2));
            }
            inline Vector2 Normalized()
            {
                return Vector2(x > 0 ? x / Magnitude() : 0, y > 0 ? y / Magnitude() : 0);
            }
            inline Vector2 OverrideNormalized()
            {
                x = x > 0 ? x / Magnitude() : 0;
                y = y > 0 ? y / Magnitude() : 0;

                return *this;
            }

            inline static Vector2 Direction(const Vector2* from, const Vector2* to)
            {
                return *from - *to;
            }
        };
        struct Vector3Euler
        {
        private:
            float x;
            float y;
            float z;
        public:
            enum class AXYS { X, Y, Z };

            inline const float Get(const AXYS axys) const
            {
                switch (axys)
                {
                case AXYS::X:
                    return x;
                case AXYS::Y:
                    return y;
                case AXYS::Z:
                    return z;
                default:
                    return NULL;
                }
            }
            inline const void Set(const AXYS axys, const float value)
            {
                switch (axys)
                {
                case AXYS::X:
                    x = value;
                    break;
                case AXYS::Y:
                    y = value;
                    break;
                case AXYS::Z:
                    z = value;
                    break;
                default:
                    break;
                }
                return;
            }

            Vector3Euler(const float _x, const float _y, const float _z)
            {
                x = _x;
                y = _y;
                z = _z;
            }

            inline const Vector3Euler Zero() const
            {
                return Vector3Euler(0, 0, 0);
            }
            inline const Vector3Euler One() const
            {
                return Vector3Euler(1, 1, 1);
            }
            inline const Vector3Euler Up() const
            {
                return Vector3Euler(0, 1, 0);
            }
            inline const Vector3Euler Down() const
            {
                return Vector3Euler(0, -1, 0);
            }
            inline const Vector3Euler Left() const
            {
                return Vector3Euler(-1, 0, 0);
            }
            inline const Vector3Euler Right() const
            {
                return Vector3Euler(1, 0, 0);
            }
            inline const Vector3Euler Front() const
            {
                return Vector3Euler(0, 0, 1);
            }
            inline const Vector3Euler Back() const
            {
                return Vector3Euler(0, 0, -1);
            }


            inline Vector3Euler operator + (const Vector3Euler& other) const
            {
                return Vector3Euler(other.x + x, other.y + y, z + other.z);
            }
            inline Vector3Euler operator - (const Vector3Euler& other) const
            {
                return Vector3Euler(x - other.x, y - other.y, z - other.z);
            }
            inline Vector3Euler operator * (const float& other) const
            {
                return Vector3Euler(x * other, y * other, z * other);
            }

            inline float Magnitude()
            {
                return sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2));
            }
            inline Vector3Euler Normalized()
            {
                return Vector3Euler(x > 0 ? x / Magnitude() : 0, y > 0 ? y / Magnitude() : 0, z > 0 ? z / Magnitude() : 0);
            }
            inline Vector3Euler OverrideNormalized()
            {
                x = x > 0 ? x / Magnitude() : 0;
                y = y > 0 ? y / Magnitude() : 0;
                z = z > 0 ? z / Magnitude() : 0;

                return *this;
            }

            inline static Vector3Euler Direction(const Vector3Euler* from, const Vector3Euler* to)
            {
                return *from - *to;
            }
        };
    }
}