/**
  * @file Vector.h
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
#ifndef DIVISIONCORE_VECTOR_H
#define DIVISIONCORE_VECTOR_H
#include <cmath>
#include <cstdarg>
#include <array>

namespace DivisionCore { namespace Vectors {

        template<size_t N, typename T>struct Vector;
        typedef Vector<1,float> Vector1;
        typedef Vector<2,float> Vector2;
        typedef Vector<3,float> Vector3;
        typedef Vector<4,float> Vector4;
        typedef Vector<5,float> Vector5;

    template<size_t N = 2, typename T = float >
        struct Vector{
        public:
            std::array<T,N> coords;

            T * x = &coords[0];
            T * y = &coords[1];
            T * z = &coords[2];
            T * u = &coords[3];
            T * v = &coords[4];
            T * w = &coords[5];

            Vector<N,T>()
            {
                for(int i = 0; i < N; i++)
                {
                    coords[i] = 0;
                }
            };

            explicit Vector<N,T>(const T& coord, ...)
            {
                va_list list;

                va_start(list, coord);

                 for(int i = 0; i < N; i++)
                 {
                     if(&va_arg(list, T) != nullptr)
                     {
                         coords[i] = va_arg(list, T);
                     }
                     else
                     {
                         coords[i] = 0;
                     }
                 }
            }
            Vector<N,T>(const T& unique, bool )
            {
                for(int i = 0; i < N; i++)
                {
                    coords[i] = unique;
                }
            }
            Vector<N,T>(const Vector<N,T>& from, const Vector<N,T>& to)
            {
                Vector<N,T> temp = from - to;

                for(int i = 0; i < N; i++)
                {
                   coords[i] = temp.coords[i];
                }
            }
            ~Vector()
            {
                delete x;
                delete y;
                delete z;
                delete u;
                delete v;
                delete w;
            }

            static inline Vector<N,T> Zero()
            {
                return Vector<N,T>(0, true);
            }
            static inline Vector<N,T> One()
            {
                return Vector<N,T>(1, true);
            }
            static inline Vector<N,T> Up()
            {
                return Vector<N,T>{0, 1};
            }
            static inline Vector<N,T> Down()
            {
                return Vector<N,T>{0, -1};
            }
            static inline Vector<N,T> Left()
            {
                return Vector<N,T>{-1, 0};
            }
            static inline Vector<N,T> Right()
            {
                return Vector<N,T>{1, 0};
            }
            static inline Vector<N,T> Front() {
                return Vector<N,T>{0, 0, 1};
            }
            static inline Vector<N,T> Back() {
                return Vector<N,T>{0, 0, -1};
            }

            inline Vector<N,T> operator + (const Vector<N,T>& other) const
            {
                Vector<N,T> temp = Vector<N,T>::Zero();

                for(int i = 0; i < N; i++)
                {
                   temp[i] = other.coords[i] + coords[i];
                }

                return temp;
            }
            inline Vector<N,T> operator - (const Vector<N,T>& other) const
            {
                Vector<N,T> temp = Vector<N,T>::Zero();

                for(int i = 0; i < N; i++)
                {
                    temp[i] = other.coords[i] - coords[i];
                }

                return temp;
            }
            inline Vector<N,T> operator * (const float& other) const
            {
                Vector<N,T> temp = Vector<N,T>::Zero();

                for(int i = 0; i < N; i++)
                {
                    temp[i] = other * coords[i];
                }

                return temp;
            }

            inline Vector<N,T> operator += (const Vector<N,T>& other)
            {
                for(int i = 0; i < N; i++)
                {
                    coords[i] = other.coords[i] + coords[i];
                }

                return *this;
            }
            inline Vector<N,T> operator -= (const Vector<N,T>& other)
            {
                for(int i = 0; i < N; i++)
                {
                    coords[i] = other.coords[i] - coords[i];
                }

                return *this;
            }
            inline Vector<N,T> operator *= (const float& other)
            {
                for(int i = 0; i < N; i++)
                {
                    coords[i] = other * coords[i];
                }

                return *this;
            }

            inline bool operator == (const Vector<N,T>& other) const
            {
                for(int i = 0; i < N; i++)
                {
                    if(other.coords[i] != coords[i])
                    {
                        return false;
                    }
                }
                return true;
            }
            inline bool operator != (const Vector<N,T>& other) const
            {
                for(int i = 0; i < N; i++)
                {
                    if(other.coords[i] == coords[i])
                    {
                        return false;
                    }
                }
                return true;
            }

            inline Vector<N,T>& operator = (const Vector<N,T>& other)
            {
                if(&other != this)
                {
                    for (int i = 0; i < N; ++i)
                    {
                        coords[i] = other.coords[i];
                    }
                }

                return *this;
            }

            inline float Magnitude() const
            {
                T temp = 0;

                for(int i = 0; i < N; i++)
                {
                    temp += coords[i] * coords[i];
                }

                return temp;
            }
            inline Vector<N,T> Normalized() const
            {
                Vector<N,T> temp = Vector<N,T>::Zero();

                for(int i = 0; i < N; i++)
                {
                    temp[i] = temp[i] > 0 ? temp[i] / Magnitude() : 0;
                }

                return temp;
            }
            inline Vector<N,T> OverrideNormalized()
            {
                for(int i = 0; i < N; i++)
                {
                    coords[i] = coords[i] > 0 ? coords[i] / Magnitude() : 0;
                }

                return *this;
            }
        };
    }}
#endif //DIVISIONCORE_VECTOR_H
