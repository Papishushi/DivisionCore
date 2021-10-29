/**
  * @file GameController.h
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
#ifndef DIVISIONCORE_GAMECONTROLLER_H
#define DIVISIONCORE_GAMECONTROLLER_H
#include "RunningBehaviour.h"

namespace DivisionCore { namespace Core { namespace BehaviourSystem { namespace Components {

    class GameController : protected DivisionCore::Core::BehaviourSystem::RunningBehaviour{
        public:

            static GameController * singleton;

            GameController()
            {
                if(singleton == nullptr)
                {
                    singleton = this;
                }
                else
                {
                    Destroy(this) ;
                }
            }
            explicit GameController(bool rewrite)
            {
                if(rewrite || singleton == nullptr)
                {
                    singleton = this;
                }
                else
                {
                    Destroy(this) ;
                }
            }
            ~GameController()
            {
                singleton = nullptr;
            }
        };
 } } } }
#endif //DIVISIONCORE_GAMECONTROLLER_H