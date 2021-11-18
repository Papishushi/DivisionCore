/**
  * @file EventEmitter.h
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
#ifndef DIVISIONCORE_EVENTEMITTER_H
#define DIVISIONCORE_EVENTEMITTER_H

#include "EventHandler.h"
#include "EventObserver.h"

#include <memory>

namespace DivisionCore {
    namespace Core {
        namespace EventHandling {

            template<typename EmisorType, typename ObserverType, typename Args>
            class EventEmitter {
            private:
                bool emits;
                std::shared_ptr<EmisorType> input1;
                std::shared_ptr<Args> input2;
            public:

                EventEmitter() {
                    emits = false;
                }

                explicit EventEmitter(const EventEmitter * clone){
                    if(this != clone)
                    {
                        this->emits = clone->emits;
                        this->input1 = clone->input1;
                        this->input2 = clone->input2;
                    }

                };

                inline bool IsEmitting() const { return emits; }

                inline std::shared_ptr<EmisorType> GetInput1() const {
                    return input1;
                }

                inline std::shared_ptr<Args> GetInput2() const {
                    return input2;
                }

                virtual void Emit(std::shared_ptr<EmisorType> _input1, std::shared_ptr<Args> _input2) {
                    emits = true;

                    input1 = _input1;
                    input2 = _input2;
                }

                virtual std::shared_ptr<EventHandler<EmisorType, ObserverType, Args>>
                        Bind(std::shared_ptr<ObserverType> eventObserver, void (ObserverType::*pFunction)(std::shared_ptr<EmisorType>, const std::shared_ptr<Args>)) {

                    auto temp = reinterpret_cast<EventObserver<EmisorType, ObserverType, Args> *>(eventObserver.get());
                    return temp->Bind(pFunction, std::make_shared<EventEmitter<EmisorType,ObserverType,Args>>(this));
                }

                virtual void Unbind(std::shared_ptr<EventObserver<EmisorType, ObserverType, Args>> eventObserver,
                                    EventHandler<EmisorType, ObserverType, Args> &handler) {

                    eventObserver->Unbind(handler);
                }
            };

        }
    }
}
#endif //DIVISIONCORE_EVENTEMITTER_H
