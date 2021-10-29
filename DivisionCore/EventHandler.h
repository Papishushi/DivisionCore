/**
  * @file EventHandler.h
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
#ifndef DIVISIONCORE_EVENTHANDLER_H
#define DIVISIONCORE_EVENTHANDLER_H

namespace DivisionCore { namespace Core { namespace EntitySystem{
            class GameObject;
        }}}
namespace DivisionCore { namespace Core { namespace BehaviourSystem{
            class RunningBehaviour;
        }}}

namespace DivisionCore { namespace Core {
            struct MessageArgs;
        }}

namespace DivisionCore { namespace Core { namespace EventHandling {

            template <typename T, typename C>
            class EventEmitter;

            struct EventHandler {
            public:
                BehaviourSystem::RunningBehaviour * associattedBehaviour;
                bool unbind;
                bool isObserving;

                void (*pFunction)(EntitySystem::GameObject *, MessageArgs *);

                EventEmitter <EntitySystem::GameObject, MessageArgs> *emitter;

                EventHandler() = delete;
                EventHandler(void (*_pFunction)(EntitySystem::GameObject *, MessageArgs *), EventEmitter <EntitySystem::GameObject, MessageArgs> * _emitter);
            };
        }}}
#endif //DIVISIONCORE_EVENTHANDLER_H

