/**
  * @file Component.h
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
#ifndef DIVISIONCORE_COMPONENT_H
#define DIVISIONCORE_COMPONENT_H
#include "Object.h"

#include <memory>
#include <string>

namespace DivisionCore
{
    class Transform;
    class GameObject;
    class Component : public Object<Component> {
    public:
        GameObject * gameObject;
        Transform * transform;
        string tag;

        Component();
        explicit Component(GameObject* parent);

        inline bool CompareTag(const string& _tag) const
        {
            return tag == _tag;
        }

        void SendMessageLocal(const void* Method);
        void SendMessageChildren(const void* Method);
        void SendMessageParent(const void* Method);

        template <typename T> bool TryGetComponent(T& outComponent);

        template <typename T> T GetComponent();
        template <typename T> T GetComponentInChildren();
        template <typename T> T GetComponentInParent();
        template <typename T> T* GetComponents();
        template <typename T> T* GetComponentsInChildren();
        template <typename T> T* GetComponentsInParent();
    };
}
#endif //DIVISIONCORE_COMPONENT_H

