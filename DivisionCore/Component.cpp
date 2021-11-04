/**
  * @file Component.cpp
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

#include "GameObject.h"

using namespace DivisionCore::Core;
using namespace DivisionCore::Core::EntitySystem;
using namespace DivisionCore::Core::BehaviourSystem;

using DivisionCore::Containers::TemplateDictionary;
using DivisionCore::Containers::Dictionary;

template <typename T> TemplateDictionary<typename Object<T>::dynamic_byte,Object, T > Object<T>::idInstanceDictionary;
template <typename T> Dictionary<typename Object<T>::dynamic_byte, string> Object<T>::hideFlagsLookupTable;

namespace DivisionCore { namespace Core { namespace BehaviourSystem
{
    Component::Component() {
        (void)&hideFlagsLookupTable;
        (void)&idInstanceDictionary;

        gameObject = new GameObject();
        transform = &(gameObject->transform);
        tag = nullptr;
    }
    Component::Component(GameObject * parent) {
        (void)&hideFlagsLookupTable;
        (void)&idInstanceDictionary;

        gameObject = parent;
        transform = &(parent->transform);
        tag = nullptr;
    }

    void Component::SendMessageLocal(GameObject * emisor, MessageArgs * args) const {
        gameObject->SendMessageLocal.Emit(emisor,args);
    }

    void Component::SendMessageChildren(GameObject * emisor, MessageArgs * args) const {
        gameObject->SendMessageChildren.Emit(emisor,args);
    }

    void Component::SendMessageParent(GameObject * emisor, MessageArgs * args) const {
        gameObject->SendMessageParent.Emit(emisor,args);
    }

    template<typename T>
    bool Component::TryGetComponent(T& outComponent) {
        return gameObject->TryGetComponent(outComponent);
    }

    template <typename T>
    T Component::GetComponent()
    {
        return gameObject->GetComponent<T>();
    }
    template <typename T>
    T Component::GetComponentInChildren()
    {
        return gameObject->GetComponentInChildren<T>();
    }
    template <typename T>
    T Component::GetComponentInParent()
    {
        return gameObject->GetComponentInParent<T>();
    }
    template <typename T>
    T* Component::GetComponents()
    {
        return gameObject->GetComponents<T>();
    }
    template <typename T>
    T* Component::GetComponentsInChildren()
    {
        return gameObject->GetComponentsInChildren<T>();
    }
    template <typename T>
    T* Component::GetComponentsInParent()
    {
        return gameObject->GetComponentsInParent<T>();
    }
} } }