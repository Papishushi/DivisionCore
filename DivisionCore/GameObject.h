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
#include "MessageArgs.h"
#include "PrimitiveType.h"
#include "EventEmitter.h"
#include "EventHandler.h"

#include <string>
#include <list>
#include <iterator>
#include <utility>

using DivisionCore::Core::BehaviourSystem::Components::Transform;

namespace DivisionCore {
    namespace Core {
        namespace BehaviourSystem {
            class RunningBehaviour;
        }
    }
}

using DivisionCore::Core::BehaviourSystem::RunningBehaviour;

using std::list;

namespace DivisionCore {
    namespace Core {
        namespace EntitySystem {
            class GameObject : protected Object<GameObject> {
            private:
                static std::list<std::shared_ptr<GameObject>> instancedGameObjects;
                std::list<std::shared_ptr<RunningBehaviour>> attachedComponents;
                bool isActive;
            protected:
                std::list<std::shared_ptr<EventHandling::EventHandler<GameObject, RunningBehaviour, MessageArgs>>> UpdateMessageLink();
                inline void AddInstance(){
                    instancedGameObjects.push_back(std::make_shared<GameObject>(this));
                }
            public:
                bool activeInHierarchy;

                inline bool activeSelf() const {
                    return isActive;
                }

                bool isStatic;
                uint_least8_t layer;
                uint_least8_t scene;
                unsigned long sceneCullingMask;
                string tag;
                Transform transform;

                EventHandling::EventEmitter<GameObject, RunningBehaviour, MessageArgs> SendMessageLocal;
                EventHandling::EventEmitter<GameObject, RunningBehaviour, MessageArgs> SendMessageChildren;
                EventHandling::EventEmitter<GameObject, RunningBehaviour, MessageArgs> SendMessageParent;

                GameObject();

                explicit GameObject(string &name);

                explicit GameObject(string &name, Transform &transform);

                explicit GameObject(string &name, Transform &transform,
                                    const std::list<std::shared_ptr<RunningBehaviour>> &components);

                explicit GameObject(const GameObject& clone);
                explicit GameObject(const std::unique_ptr<GameObject> clone);
                explicit GameObject(const GameObject *clone);

                ~GameObject();

                inline void SetActive(const bool _isActive) {
                    isActive = _isActive;
                }

                template<typename T>
                inline T *AddComponent() {
                    T *temp = new T();
                    attachedComponents.push_back(temp);
                    return temp;
                }

                template<typename T>
                inline void DestroyComponent(T *_component) {
                    if (_component != nullptr) {
                        attachedComponents.remove(_component);
                        Destroy(_component);
                    }
                }

                inline bool CompareTag(const string &_tag) const {
                    return tag == _tag;
                }

                template<typename T>
                bool TryGetComponent(T &outComponent) {
                    list<std::shared_ptr<RunningBehaviour>>::iterator it;

                    for (it = attachedComponents.begin(); it != attachedComponents.end(); ++it) {
                        if (dynamic_cast<T *>(it) != nullptr) {
                            outComponent = it;
                            return true;
                        }
                    }
                    return false;
                }

                template<typename T>
                T GetComponent() {
                    list<std::shared_ptr<RunningBehaviour>>::iterator it;

                    for (it = attachedComponents.begin(); it != attachedComponents.end(); ++it) {
                        if (dynamic_cast<T>(it) != nullptr) {
                            return it;
                        }
                    }
                    return nullptr;
                }

                template<typename T>
                T GetComponentInChildren() {
                    list<std::shared_ptr<RunningBehaviour>>::iterator it;
                    list<Transform>::iterator itChildren;

                    for (itChildren = transform.children.begin();
                         itChildren != transform.children.end(); ++itChildren) {
                        for (it = itChildren->gameObject->attachedComponents.begin();
                             it != itChildren->gameObject->attachedComponents.end(); ++it) {
                            if (dynamic_cast<T>(it) != nullptr) {
                                return it;
                            }
                        }
                    }

                    return nullptr;
                }

                template<typename T>
                T GetComponentInParent() {
                    list<std::shared_ptr<RunningBehaviour>>::iterator it;
                    for (it = transform.parent->gameObject->attachedComponents.begin();
                         it != transform.parent->gameObject->attachedComponents.end(); ++it) {
                        if (dynamic_cast<T>(it) != nullptr) {
                            return it;
                        }
                    }

                    return nullptr;
                }

                template<typename T>
                T *GetComponents() {
                    std::unique_ptr<T> tempArr = nullptr;
                    dynamic_byte counter = 0;

                    list<std::shared_ptr<RunningBehaviour>>::iterator it;

                    for (it = attachedComponents.begin(); it != attachedComponents.end(); ++it) {
                        if (dynamic_cast<std::unique_ptr<T>>(it) != nullptr) {
                            ExpandAddArray(tempArr, counter, counter + 1, it);
                            counter++;
                        }
                    }

                    return tempArr;
                }

                template<typename T>
                T *GetComponentsInChildren() {
                    T *tempArr = nullptr;
                    dynamic_byte counter = 0;

                    list<std::shared_ptr<RunningBehaviour>>::iterator it;
                    list<Transform>::iterator itChildren;
                    for (itChildren = transform.children.begin();
                         itChildren != transform.children.end(); ++itChildren) {
                        for (it = transform.parent->gameObject->attachedComponents.begin();
                             it != transform.parent->gameObject->attachedComponents.end(); ++it) {
                            if (dynamic_cast<T *>(it) != nullptr) {
                                ExpandAddArray(tempArr, counter, counter + 1, it);
                                counter++;
                            }
                        }
                    }

                    return tempArr;
                }

                template<typename T>
                T *GetComponentsInParent() {
                    T *tempArr = nullptr;
                    dynamic_byte counter = 0;

                    list<std::shared_ptr<RunningBehaviour>>::iterator it;

                    for (it = transform.parent->gameObject->attachedComponents.begin();
                         it != transform.parent->gameObject->attachedComponents.end(); ++it) {
                        if (dynamic_cast<T *>(it) != nullptr) {
                            ExpandAddArray(tempArr, counter, counter + 1, it);
                            counter++;
                        }
                    }

                    return tempArr;
                }

                static GameObject *CreatePrimitive(PrimitiveType primitiveType);

                static GameObject Find(const string &name);

                static GameObject *FindGameObjectsWithTag(const string &tag);

                static GameObject FindWithTag(const string &tag);
            };
        }
    }
}
#endif //DIVISIONCORE_GAMEOBJECT_H