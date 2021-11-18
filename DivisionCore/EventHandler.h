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
#include <memory>

#ifdef _WIN32

#include <windows.h>

#else
#include <unistd.h>
#include <thread>
#endif

namespace DivisionCore {
    namespace Core {
        namespace EventHandling {

            template<typename EmisorType, typename ObserverType, typename Args>
            class EventEmitter;

            template<typename EmisorType, typename ObserverType, typename Args>
            class EventObserver;

            template<typename EmisorType, typename ObserverType, typename Args>
            struct EventHandler {
            public:
                std::shared_ptr<ObserverType> associattedBehaviour;
                bool unbind;
                bool isObserving;

                void (ObserverType::* pFunction)(std::shared_ptr<EmisorType>, const std::shared_ptr<Args>);

                std::shared_ptr<EventEmitter<EmisorType, ObserverType, Args>> emitter;
                std::shared_ptr<EventObserver<EmisorType, ObserverType, Args>> observer;

                EventHandler() = delete;

                EventHandler(void (ObserverType::*_pFunction)(std::shared_ptr<EmisorType>, const std::shared_ptr<Args>),
                             std::shared_ptr<EventEmitter<EmisorType, ObserverType, Args>> _emitter,
                             std::shared_ptr<EventObserver<EmisorType, ObserverType, Args>> _observer) {
                    pFunction = _pFunction;
                    emitter = _emitter;
                    observer = _observer;

                    associattedBehaviour.reset(reinterpret_cast<ObserverType *>(observer.get()));

                    while (true) {
                        isObserving = true;

#if _WIN32
                        Sleep(5);
#elif __linux__
                        using namespace std::literals;
                        std::this_thread::sleep_for(5ms);
#else __APPLE__
                        sleep(0.005f);
#endif
                        if (emitter->IsEmitting()) {
                            //Member hook pointer call
                            (associattedBehaviour.get()->*pFunction)(emitter->GetInput1(), emitter->GetInput2());
                        }

                        if (unbind) {
                            isObserving = false;
                            unbind = false;
                            return;
                        }
                    }
                }
            };
        }
    }
}
#endif //DIVISIONCORE_EVENTHANDLER_H

