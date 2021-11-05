/**
  * @file RunningBehaviour.h
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
#ifndef DIVISIONCORE_RUNNINGBEHAVIOUR_H
#define DIVISIONCORE_RUNNINGBEHAVIOUR_H
#include "Behaviour.h"
#include "GameObject.h"
#include "MessageArgs.h"
#include "EventObserver.h"
#include "Dictionary.h"
#include <iterator>
#include <string>

using DivisionCore::Core::EntitySystem::GameObject;
using DivisionCore::Core::EventHandling::EventObserver;

namespace DivisionCore{ namespace Core { namespace BehaviourSystem
{
class RunningBehaviour : public Behaviour, public EventObserver<GameObject, MessageArgs>
    {
    private:
        enum class MethodsEnum
        {
            Destroy = 0,
            HookMessage = 1
        };
    protected:
        static Dictionary<string, uint_least8_t > methodsLookUpTable;

        inline virtual void InitializeLookUpTable() const
        {
            methodsLookUpTable.Add(KeyValuePair<string, uint_least8_t>::MakePair("Destroy", (uint_least8_t)MethodsEnum::Destroy));
            methodsLookUpTable.Add(KeyValuePair<string, uint_least8_t>::MakePair("HookMessage", (uint_least8_t)MethodsEnum::HookMessage));
        }
        void HookMessage(GameObject * source, const MessageArgs* args);

        virtual void SearchLookUpTable(MethodsEnum &out, const string& search);

        virtual void ProcessLookUpValue(GameObject *source, const MessageArgs *args, const MethodsEnum &value) ;

        virtual void Awake() = 0;
        virtual void Start()  = 0;
        virtual void FixedUpdate()  = 0;
        virtual void Update()  = 0;
        virtual void LateUpdate()  = 0;

        void (RunningBehaviour::*pHook) (GameObject *,const MessageArgs *) = &RunningBehaviour::HookMessage;
    public:
    RunningBehaviour();
    template <typename T = void (RunningBehaviour::*) (GameObject *,const MessageArgs *)>
        inline T GetHook()
        {
            return pHook;
        }
    };
}}}
#endif //DIVISIONCORE_RUNNINGBEHAVIOUR_H