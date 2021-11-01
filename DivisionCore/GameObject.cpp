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


#include "Transform.h"
#include "MessageArgs.h"
#include "PrimitiveType.h"
#include "GameObject.h"
#include "RunningBehaviour.h"
#include "EventObserver.h"
#include "EventEmitter.h"
#include "EventHandler.h"

#include <iterator>
#include <list>

using namespace std;
using namespace DivisionCore::Core::BehaviourSystem;
using namespace DivisionCore::Core::BehaviourSystem::Components;

namespace DivisionCore { namespace Core { namespace EntitySystem
{
    GameObject::GameObject() {
        transform = Transform();
        instancedGameObjects.push_back(this);
        isActive = true;
        isStatic = false;
        activeInHierarchy = true;
        layer = 0;
        scene = 0;
        sceneCullingMask = 0;
        tag = nullptr;

        UpdateMessageLink();
    }

    GameObject::GameObject(string &name) {
        this->name = name;
        transform = Transform();
        instancedGameObjects.push_back(this);
        isActive = true;
        isStatic = false;
        activeInHierarchy = true;
        layer = 0;
        scene = 0;
        sceneCullingMask = 0;
        tag = nullptr;

        UpdateMessageLink();
    }

    GameObject::GameObject(string &name, Transform &transform) {
        this->name = name;
        hideFlags = HideFlags::VISIBLE;
        this->transform = transform;
        instancedGameObjects.push_back(this);
        isActive = true;
        isStatic = false;
        activeInHierarchy = true;
        layer = 0;
        scene = 0;
        sceneCullingMask = 0;
        tag = nullptr;

        UpdateMessageLink();
    }

    GameObject::GameObject(string &name, Transform &transform, const list <RunningBehaviour *> &components) {
        this->name = name;
        hideFlags = HideFlags::VISIBLE;
        this->transform = transform;
        attachedComponents = components;
        instancedGameObjects.push_back(this);
        isActive = true;
        isStatic = false;
        activeInHierarchy = true;
        layer = 0;
        scene = 0;
        sceneCullingMask = 0;
        tag = nullptr;

        UpdateMessageLink();
    }

    GameObject::~GameObject() {
        instancedGameObjects.remove(this);
    }

    list<EventHandling::EventHandler *> GameObject::UpdateMessageLink()
    {
        void (* pFunction) (GameObject*, MessageArgs*) = nullptr;

        list<EventHandling::EventHandler *> handlers;

        list<RunningBehaviour *>::iterator it;
        list<Transform>::iterator itChildren;
        for (it = attachedComponents.begin(); it != attachedComponents.end(); ++it)
        {
            pFunction = (*it)->GetHook();

            if(pFunction)
            {
                EventHandling::EventHandler * handler = SendMessageLocal.Bind(*it, pFunction);

                if(handler)
                {
                    handlers.push_back(handler);
                }
            }

        }
        for (itChildren = transform.children.begin(); itChildren != transform.children.begin(); ++itChildren)
        {
            for (it = itChildren->gameObject->attachedComponents.begin(); it != itChildren->gameObject->attachedComponents.end(); ++it)
            {
                pFunction = (*it)->GetHook();

                if(pFunction)
                {
                    EventHandling::EventHandler * handler = SendMessageChildren.Bind(*it, pFunction);

                    if(handler)
                    {
                        handlers.push_back(handler);
                    }
                }
            }
        }
        for (it = transform.parent->gameObject->attachedComponents.begin(); it != transform.parent->gameObject->attachedComponents.end(); ++it)
        {
            pFunction = (*it)->GetHook();

            if(pFunction)
            {
                EventHandling::EventHandler * handler = SendMessageParent.Bind(*it, pFunction);

                if(handler)
                {
                    handlers.push_back(handler);
                }
            }
        }

        return handlers;
    }

    //Incomplete coding must finalize it
    GameObject * GameObject::CreatePrimitive(PrimitiveType primitiveType)
    {
        switch (primitiveType)
        {
            case PrimitiveType::SQUARE:
                return Instantiate(GameObject(), "Square");
            case PrimitiveType::CIRCLE:
                return Instantiate(GameObject(), "Circle");
            case PrimitiveType::TRIANGLE:
                return Instantiate(GameObject(), "Triangle");
            case PrimitiveType::HEXAGON:
                return Instantiate(GameObject(), "Hexagon");
            default:
                return nullptr;
        }
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
} } }