#pragma once

#include <cmath>

using namespace std;

namespace DivisionCore { namespace Vectors
{
    struct Vector3Euler
    {
    private:
        float x{}, y{} ,z{};
    public:
        enum class AXYS { X, Y, Z };
        
        inline float Get(const AXYS axys) const
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
        inline void Set(const AXYS axys, const float& value)
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
        }
        Vector3Euler() = default;
        Vector3Euler(const Vector3Euler& from, const Vector3Euler& to)
        {
            Vector3Euler temp = from - to;
            x = temp.x;
            y = temp.y;
            z = temp.z;
        }
        Vector3Euler(const float& _x, const float& _y, const float& _z)
        {
            x = _x;
            y = _y;
            z = _z;
        }
        
        static inline Vector3Euler Zero()
        {
            return Vector3Euler{0, 0, 0};
        }
        static inline Vector3Euler One()
        {
            return Vector3Euler{1, 1, 1};
        }
        static inline Vector3Euler Up()
        {
            return Vector3Euler{0, 1, 0};
        }
        static inline Vector3Euler Down()
        {
            return Vector3Euler{0, -1, 0};
        }
        static inline Vector3Euler Left()
        {
            return Vector3Euler{-1, 0, 0};
        }
        static inline Vector3Euler Right()
        {
            return Vector3Euler{1, 0, 0};
        }
        static inline Vector3Euler Front()
        {
            return Vector3Euler{0, 0, 1};
        }
        static inline Vector3Euler Back()
        {
            return Vector3Euler{0, 0, -1};
        }
        
        
        inline Vector3Euler operator + (const Vector3Euler& other) const
        {
            return Vector3Euler{other.x + x, other.y + y, z + other.z};
        }
        inline Vector3Euler operator - (const Vector3Euler& other) const
        {
            return Vector3Euler{x - other.x, y - other.y, z - other.z};
        }
        inline Vector3Euler operator * (const float& other) const
        {
            return Vector3Euler{x * other, y * other, z * other};
        }
        inline bool operator == (const Vector3Euler& other) const
        {
            return x == other.x && y == other.y && z == other.z;
        }
        inline bool operator != (const Vector3Euler& other) const
        {
            return x != other.x && y != other.y && z != other.z;
        }
        
        inline float Magnitude() const
        {
            return sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2));
        }
        inline Vector3Euler Normalized() const
        {
            return Vector3Euler{x > 0 ? x / Magnitude() : 0, y > 0 ? y / Magnitude() : 0, z > 0 ? z / Magnitude() : 0};
        }
        inline Vector3Euler OverrideNormalized()
        {
            x = x > 0 ? x / Magnitude() : 0;
            y = y > 0 ? y / Magnitude() : 0;
            z = z > 0 ? z / Magnitude() : 0;
            
            return *this;
        }
    };
} }
