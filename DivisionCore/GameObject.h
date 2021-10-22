/**
  * @file GameObject.h
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
#ifndef DIVISIONCORE_GAMEOBJECT_H
#define DIVISIONCORE_GAMEOBJECT_H
#include "Transform.h"
#include "Component.h"

#include <list>
#include <iterator>

namespace DivisionCore
{
    enum class PrimitiveType
    {
        SQUARE = 0,
        CIRCLE = 1,
        TRIANGLE = 2,
        HEXAGON = 3
    };

    class GameObject : protected Object<GameObject>
    {
    private:
        static list<GameObject> instancedGameObjects;
        list<DivisionCore::Component> attachedComponents;
        bool isActive;
    public:
        bool activeInHierarchy;
        inline bool activeSelf() const
        {
            return isActive;
        }
        bool isStatic;
        uint_least8_t layer;
        uint_least8_t scene;
        unsigned long sceneCullingMask;
        string tag;
        Transform transform;

        GameObject();
        explicit GameObject(string& name);
        explicit GameObject(string& name, Transform& transform);
        explicit GameObject(string& name, Transform& transform, const list<DivisionCore::Component>& components);
        GameObject(const GameObject& gameObject);

        inline void SetActive(const bool _isActive)
        {
            isActive = _isActive;
        }
        template <typename T> inline T AddComponent()
        {
            T* temp = new T();
            attachedComponents.push_back(temp);
            return temp;
        }

        inline bool CompareTag(const string& _tag) const
        {
            return tag == _tag;
        }

        void SendMessageLocal(const void* method);
        void SendMessageChildren(const void* method);
        void SendMessageParent(const void* method);

        template <typename T> bool TryGetComponent(T& outComponent)
        {
            list<Component>::iterator it;

            for (it = attachedComponents.begin(); it != attachedComponents.end(); ++it)
            {
                if (dynamic_cast<T*>(it) != nullptr)
                {
                    outComponent = it;
                    return true;
                }
            }
            return false;
        }

        template <typename T> T GetComponent()
        {
            list<Component>::iterator it;

            for (it = attachedComponents.begin(); it != attachedComponents.end(); ++it)
            {
                if (dynamic_cast<T>(it) != nullptr)
                {
                    return it;
                }
            }
            return nullptr;
        }
        template <typename T> T GetComponentInChildren();
        template <typename T> T GetComponentInParent();
        template <typename T> T* GetComponents();
        template <typename T> T* GetComponentsInChildren();
        template <typename T> T* GetComponentsInParent();

        static GameObject CreatePrimitive(PrimitiveType primitiveType);
        static GameObject Find(string name);
        static GameObject* FindGameObjectsWithTag(string tag);
        static GameObject FindWithTag(string tag);
    };
}
#endif //DIVISIONCORE_GAMEOBJECT_H

