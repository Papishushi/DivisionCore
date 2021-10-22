/**
  * @file Vector3Euler.h
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
#ifndef DIVISIONCORE_VECTOR3EULER_H
#define DIVISIONCORE_VECTOR3EULER_H

#include <cmath>

namespace DivisionCore { namespace Vectors {
        struct Vector3Euler {
        private:
            float x{}, y{}, z{};
        public:
            enum class AXYS {
                X, Y, Z
            };

            inline float Get(const AXYS axys) const {
                switch (axys) {
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

            inline void Set(const AXYS axys, const float &value) {
                switch (axys) {
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

            Vector3Euler(const Vector3Euler &from, const Vector3Euler &to) {
                Vector3Euler temp = from - to;
                x = temp.x;
                y = temp.y;
                z = temp.z;
            }

            Vector3Euler(const float &_x, const float &_y, const float &_z) {
                x = _x;
                y = _y;
                z = _z;
            }

            static inline Vector3Euler Zero() {
                return Vector3Euler{0, 0, 0};
            }

            static inline Vector3Euler One() {
                return Vector3Euler{1, 1, 1};
            }

            static inline Vector3Euler Up() {
                return Vector3Euler{0, 1, 0};
            }

            static inline Vector3Euler Down() {
                return Vector3Euler{0, -1, 0};
            }

            static inline Vector3Euler Left() {
                return Vector3Euler{-1, 0, 0};
            }

            static inline Vector3Euler Right() {
                return Vector3Euler{1, 0, 0};
            }

            static inline Vector3Euler Front() {
                return Vector3Euler{0, 0, 1};
            }

            static inline Vector3Euler Back() {
                return Vector3Euler{0, 0, -1};
            }


            inline Vector3Euler operator+(const Vector3Euler &other) const {
                return Vector3Euler{other.x + x, other.y + y, z + other.z};
            }

            inline Vector3Euler operator-(const Vector3Euler &other) const {
                return Vector3Euler{x - other.x, y - other.y, z - other.z};
            }

            inline Vector3Euler operator*(const float &other) const {
                return Vector3Euler{x * other, y * other, z * other};
            }

            inline bool operator==(const Vector3Euler &other) const {
                return x == other.x && y == other.y && z == other.z;
            }

            inline bool operator!=(const Vector3Euler &other) const {
                return x != other.x && y != other.y && z != other.z;
            }

            inline float Magnitude() const {
                return sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2));
            }

            inline Vector3Euler Normalized() const {
                return Vector3Euler{x > 0 ? x / Magnitude() : 0, y > 0 ? y / Magnitude() : 0,
                                    z > 0 ? z / Magnitude() : 0};
            }

            inline Vector3Euler OverrideNormalized() {
                x = x > 0 ? x / Magnitude() : 0;
                y = y > 0 ? y / Magnitude() : 0;
                z = z > 0 ? z / Magnitude() : 0;

                return *this;
            }
        };
    }
}
#endif //DIVISIONCORE_VECTOR3EULER_H
