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

#include "ObjectMacros.h"
#include "GameObject.h"

using namespace DivisionCore::Core;
using namespace DivisionCore::Core::EntitySystem;
using namespace DivisionCore::Core::BehaviourSystem;

INCLUDE_OBJECT_STATIC

namespace DivisionCore {
    namespace Core {
        namespace BehaviourSystem {
            Component::Component() {
                gameObject.reset(new GameObject());
                transform.reset(&(gameObject->transform));
                tag = nullptr;
            }

            Component::Component(std::weak_ptr<GameObject> parent) {
                std::shared_ptr<GameObject> sharedPtr = parent.lock();

                gameObject = sharedPtr;

                transform = std::make_shared<Components::Transform>(&(gameObject->transform));
                tag = nullptr;
            }

            void Component::SendMessageLocal(std::shared_ptr<GameObject> emisor, std::shared_ptr<MessageArgs> args) const {
                gameObject->SendMessageLocal.Emit(emisor, args);
            }

            void Component::SendMessageChildren(std::shared_ptr<GameObject> emisor, std::shared_ptr<MessageArgs> args) const {
                gameObject->SendMessageChildren.Emit(emisor, args);
            }

            void Component::SendMessageParent(std::shared_ptr<GameObject> emisor, std::shared_ptr<MessageArgs> args) const {
                gameObject->SendMessageParent.Emit(emisor, args);
            }

            template<typename T>
            bool Component::TryGetComponent(T &outComponent) {
                return gameObject->TryGetComponent(outComponent);
            }

            template<typename T>
            T Component::GetComponent() {
                return gameObject->GetComponent<T>();
            }

            template<typename T>
            T Component::GetComponentInChildren() {
                return gameObject->GetComponentInChildren<T>();
            }

            template<typename T>
            T Component::GetComponentInParent() {
                return gameObject->GetComponentInParent<T>();
            }

            template<typename T>
            T *Component::GetComponents() {
                return gameObject->GetComponents<T>();
            }

            template<typename T>
            T *Component::GetComponentsInChildren() {
                return gameObject->GetComponentsInChildren<T>();
            }

            template<typename T>
            T *Component::GetComponentsInParent() {
                return gameObject->GetComponentsInParent<T>();
            }
        }
    }
}