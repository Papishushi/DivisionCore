/**
  * @file Transform.h
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
#ifndef DIVISIONCORE_TRANSFORM_H
#define DIVISIONCORE_TRANSFORM_H
#include "Object.h"
#include "Vector2.h"
#include "Vector3Euler.h"
#include "Component.h"

using std::tie;

using DivisionCore::Vectors::Vector2 ;
using DivisionCore::Vectors::Vector3Euler ;

namespace DivisionCore { namespace Core { namespace BehaviourSystem { namespace Components
{
    class Transform : public Component
    {
    public:
        Vector2 position;
        Vector3Euler rotation;
        Vector2 scale;

        Transform * parent;
        list<Transform> children;

        Transform();
        explicit Transform(Transform * parent);

        inline bool operator == (const Transform& other) const
        {
            return tie(position, rotation, scale) == tie(other.position, other.rotation, other.scale);
        }
        inline bool operator != (const Transform& other) const
        {
            return tie(position, rotation, scale) != tie(other.position, other.rotation, other.scale);
        }
    };
} } } }
#endif //DIVISIONCORE_TRANSFORM_H
