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

#if __STDC_VERSION__ < 199901L
# if __GNUC__ >= 2
#  define __func__ __FUNCTION__
# else
#  define __func__ "<unknown>"
# endif
#endif

namespace DivisionCore
{
    class RunningBehaviour : public Behaviour, public sigslot::has_slots<>
    {
    private:
        enum class MethodLookUpTable
        {
            Destroy,
            HookMessage
        };
    protected:

        void Awake();
        void Start();
        void FixedUpdate();
        void Update();
        void LateUpdate();
    public:


        RunningBehaviour() = default;

        virtual void HookMessage(GameObject * source, const MessageArgs& args) ;

        virtual void ProcessLookUpTable(GameObject *source, const MessageArgs &args, const MethodLookUpTable lookUpTable) ;

    };
}
#endif //DIVISIONCORE_RUNNINGBEHAVIOUR_H