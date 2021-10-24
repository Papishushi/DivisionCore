/**
  * @file GameObject.cpp
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
#include "RunningBehaviour.h"

#include <list>

using namespace std;

namespace DivisionCore
{
    GameObject::GameObject() {
        name = "GameObject" + to_string(GetInstanceID());
        hideFlags = HideFlags::VISIBLE;
        transform = Transform();
        instancedGameObjects.push_back(*this);
        isActive = true;
        isStatic = false;
        activeInHierarchy = true;
        layer = 0;
        scene = 0;
        sceneCullingMask = 0;
        tag = nullptr;

    }

    GameObject::GameObject(string &name) {
        this->name = name;
        hideFlags = HideFlags::VISIBLE;
        transform = Transform();
        instancedGameObjects.push_back(*this);
        isActive = true;
        isStatic = false;
        activeInHierarchy = true;
        layer = 0;
        scene = 0;
        sceneCullingMask = 0;
        tag = nullptr;
    }

    GameObject::GameObject(string &name, Transform &transform) {
        this->name = name;
        hideFlags = HideFlags::VISIBLE;
        this->transform = transform;
        instancedGameObjects.push_back(*this);
        isActive = true;
        isStatic = false;
        activeInHierarchy = true;
        layer = 0;
        scene = 0;
        sceneCullingMask = 0;
        tag = nullptr;
    }

    GameObject::GameObject(string &name, Transform &transform, const list <RunningBehaviour> &components) {
        this->name = name;
        hideFlags = HideFlags::VISIBLE;
        this->transform = transform;
        attachedComponents = components;
        instancedGameObjects.push_back(*this);
        isActive = true;
        isStatic = false;
        activeInHierarchy = true;
        layer = 0;
        scene = 0;
        sceneCullingMask = 0;
        tag = nullptr;
    }


    void GameObject::UpdateMessageLink()
    {
        SendMessageLocal.disconnect_all();
        SendMessageChildren.disconnect_all();
        SendMessageParent.disconnect_all();

        list<RunningBehaviour>::iterator it;
        list<Transform>::iterator itChildren;
        for (it = attachedComponents.begin(); it != attachedComponents.end(); ++it)
        {
            SendMessageLocal.connect(&(*it), &RunningBehaviour::HookMessage);
        }
        for (itChildren = transform.children.begin(); itChildren != transform.children.begin(); ++itChildren)
        {
            for (it = itChildren->gameObject->attachedComponents.begin(); it != itChildren->gameObject->attachedComponents.end(); ++it)
            {
                SendMessageChildren.connect(&(*it), &RunningBehaviour::HookMessage);
            }
        }
        for (it = transform.parent->gameObject->attachedComponents.begin(); it != transform.parent->gameObject->attachedComponents.end(); ++it)
        {
            SendMessageParent.connect(&(*it), &RunningBehaviour::HookMessage);
        }
    }

    template<typename T>
    T GameObject::GetComponentInChildren() {
        return NULL;
    }

    template<typename T>
    T GameObject::GetComponentInParent() {
        return NULL;
    }

    template<typename T>
    T *GameObject::GetComponents() {
        return NULL;
    }

    template<typename T>
    T *GameObject::GetComponentsInChildren() {
        return NULL;
    }

    template<typename T>
    T *GameObject::GetComponentsInParent() {
        return NULL;
    }

    GameObject GameObject::CreatePrimitive(PrimitiveType primitiveType) {
        return {};
    }

    GameObject GameObject::Find(const string& name) {
        return {};
    }

    GameObject *GameObject::FindGameObjectsWithTag(const string& tag) {
        return nullptr;
    }

    GameObject GameObject::FindWithTag(const string& tag) {
        return {};
    }

}