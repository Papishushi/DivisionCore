/**
  * @file EventHandling.h
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
#ifndef DIVISIONCORE_EVENTHANDLING_H
#define DIVISIONCORE_EVENTHANDLING_H

#include <memory>
#include <windows.h>

namespace DivisionCore { namespace Core { namespace EventHandling {

            template <typename T, typename C>
            class EventObserver;

            template <typename T, typename C>
            class EventEmitter{
            private:
                bool emits;
                T * input1;
                C * input2;
            public:

                EventEmitter() {
                    emits = false;
                    input1 = nullptr;
                    input2 = nullptr;
                }

                inline bool IsEmitting() const {return emits;}

                inline T GetInput1() const {
                    return *input1;
                }
                inline C GetInput2() const {
                    return *input2;
                }

                virtual void Emit(T * _input1,C * _input2)
                {
                    emits = true;
                    input1 = _input1;
                    input2 = _input2;
                }
                virtual void Bind(EventObserver<T,C> * eventObserver, void (*pFunction)(T,C))
                {
                    eventObserver->Bind(pFunction, this);
                }
                virtual void Unbind(EventObserver<T,C> * eventObserver, void (*pFunction)(T,C) )
                {
                    eventObserver->Unbind(pFunction);
                }


            };

            template <typename P>
            struct EventHandler;

            template <typename T, typename C>
            class EventObserver{
            public:
                virtual EventHandler<EventEmitter<T,C>> * Bind(void * pFunction, EventEmitter<T,C> * emitter)
                {
                    auto * handler = new EventHandler<EventEmitter<T,C>>(pFunction,emitter);
                    return handler;
                }
                virtual void Unbind(EventHandler<EventEmitter<T,C>>& handler)
                {
                    if(handler.isObserving)
                    {
                        handler.unbind = true;
                    }

                    Sleep(5);

                    if(!handler.isObserving)
                    {
                        delete handler;
                    }
                }
            };

            template <typename E>
            struct EventHandler
            {
            private:
                bool unbind;
                bool isObserving;
            public:
                void * pFunction;
                EventEmitter<GameObject, MessageArgs> * emitter;

                EventHandler(void * _pFunction, EventEmitter<GameObject, MessageArgs> * _emitter)
                {
                    pFunction = _pFunction;
                    emitter = _emitter;

                    while(true){
                        isObserving = true;

                        Sleep(5);

                        if(emitter->IsEmitting())
                        {
                            *pFunction(emitter->GetInput1(), emitter->GetInput2());
                        }

                        if(unbind)
                        {
                            isObserving = false;
                            unbind = false;
                            return;
                        }
                    }
                }
            };
        } } }
#endif //DIVISIONCORE_EVENTHANDLING_H
