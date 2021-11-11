/**
  * @file Tile.h
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
#ifndef DIVISIONCORE_TILE_H
#define DIVISIONCORE_TILE_H

#include "Object.h"
#include "Vector.h"
#include "EventObserver.h"
#include "MessageArgs.h"
#include "Dictionary.h"

using DivisionCore::Vectors::Vector;
using DivisionCore::Vectors::Vector2;
using DivisionCore::Core::EventHandling::EventObserver;
using DivisionCore::Containers::KeyValuePair;

namespace DivisionCore { namespace Core {
        struct Tile : public Object<Tile>, EventObserver<Tile,Tile,MessageArgs>{
        private:
            unsigned state;
            static float lenght;
            static Dictionary<Vector<2,int>,Tile*> tileGrid;
        public:
            Vector<2,int> position;
            Vector2 worldPosition;

            Tile() = delete;
            explicit Tile(const Vector<2,int>& _position);
            Tile(const Vector<2,int>& _position,const float _lenght);
            virtual ~Tile() = 0;

            virtual void UpdateCycle() = 0;
            virtual inline const unsigned& getState(const MessageArgs& args) const
            {
                return state;
            }
            virtual void CompareNeighbours()
            {
                tileGrid.Add(  KeyValuePair<Vector<2,int>,Tile*>(&position,this));

            }

        };
}}

#endif //DIVISIONCORE_TILE_H
