/**
  * @file RunningBehaviour.cpp
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
#include <string>

using namespace DivisionCore::Core;
using namespace DivisionCore::Core::EntitySystem;
using namespace DivisionCore::Core::BehaviourSystem;

using DivisionCore::Containers::TemplateDictionary;
using DivisionCore::Containers::Dictionary;

template <typename T> TemplateDictionary<typename Object<T>::dynamic_byte,Object, T > Object<T>::idInstanceDictionary;
template <typename T> Dictionary<typename Object<T>::dynamic_byte, string> Object<T>::hideFlagsLookupTable;

Dictionary<string, uint_least8_t > RunningBehaviour::methodsLookUpTable;

namespace  DivisionCore { namespace Core { namespace BehaviourSystem
{

    RunningBehaviour::RunningBehaviour()
    {
        (void) &Object<Component>::idInstanceDictionary;
        (void) &hideFlagsLookupTable;
    }

    void RunningBehaviour::SearchLookUpTable(RunningBehaviour::MethodsEnum &out, const string &search)
    {
        if (methodsLookUpTable.Empty())
        {
            InitializeLookUpTable();
        }

        out = (RunningBehaviour::MethodsEnum)*methodsLookUpTable.FindValue(search);
    }

    void RunningBehaviour::ProcessLookUpValue(GameObject * source, const MessageArgs * args, const MethodsEnum &value)
    {
        switch (value)
        {
            case MethodsEnum::Destroy:
                if(reinterpret_cast<Component * >(args->params[0]) != nullptr)
                {
                    Destroy(reinterpret_cast<Component * >(args->params[0]));
                }
                else
                {
                    Object<GameObject>::Destroy(reinterpret_cast<GameObject * >(args->params[0]));
                }
            default:
                break;
        }
    }

    void RunningBehaviour::HookMessage(GameObject *source, const MessageArgs *args)
    {
        MethodsEnum lookUpValue;
        SearchLookUpTable(lookUpValue, args->methodName);

        if(!args->selfApply && this->gameObject != source || args->selfApply)
        {
            ProcessLookUpValue(source, args, lookUpValue);
            return;
        }
        else
        {
            return;
        }
    }

    void RunningBehaviour::Awake() {

    }

    void RunningBehaviour::Start() {

    }

    void RunningBehaviour::FixedUpdate() {

    }

    void RunningBehaviour::Update() {

    }

    void RunningBehaviour::LateUpdate() {

    }

} } }