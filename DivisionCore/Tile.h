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
using DivisionCore::Containers::VectorKeyValuePair;
using DivisionCore::Containers::VectorKeyDictionary;

namespace DivisionCore {
    namespace Core {
        namespace Tilemaps {
            struct Tile : public Object<Tile>, EventObserver<Tile, Tile, MessageArgs> {
            private:
                unsigned state;
                static float lenght;
                static Containers::VectorKeyDictionary<Vector, Tile *, 2, int> tileGrid;
            public:
                Vector<2, int> position;
                Vector2 worldPosition;

                Tile() = delete;

                explicit Tile(const Vector<2, int> &_position) {
                    if (lenght == 0) {
                        lenght = 1.;
                    }

                    position = _position;
                    worldPosition = Vector2(_position.coords[0] * lenght, _position.coords[0] * lenght);

                    state = 0;

                    tileGrid.Add(VectorKeyValuePair<Vector, Tile *, 2, int>(position, this));
                }

                explicit Tile(const Vector<2, int> *_position) {
                    if (lenght == 0) {
                        lenght = 1.;
                    }

                    position = *_position;
                    worldPosition = Vector2(_position->coords[0] * lenght, _position->coords[0]);

                    state = 0;

                    tileGrid.Add(VectorKeyValuePair<Vector, Tile *, 2, int>(position, this));
                }

                virtual ~Tile() {
                    tileGrid.Remove(position);
                }

                virtual void UpdateCycle() = 0;

                virtual inline const unsigned &getState(const MessageArgs &args) const {
                    return state;
                }

                virtual void CompareNeighbours() {
                    //Alloc
                    Tile *neighbours[3][3];

                    neighbours[1][2] = *tileGrid.FindValue(position + Vector<2, int>::Up());
                    neighbours[1][0] = *tileGrid.FindValue(position + Vector<2, int>::Down());
                    neighbours[0][1] = *tileGrid.FindValue(position + Vector<2, int>::Left());
                    neighbours[2][1] = *tileGrid.FindValue(position + Vector<2, int>::Right());

                    neighbours[2][2] = *tileGrid.FindValue(position + Vector<2, int>::Up() + Vector<2, int>::Right());
                    neighbours[0][2] = *tileGrid.FindValue(position + Vector<2, int>::Up() + Vector<2, int>::Left());
                    neighbours[2][0] = *tileGrid.FindValue(position + Vector<2, int>::Down() + Vector<2, int>::Right());
                    neighbours[0][0] = *tileGrid.FindValue(position + Vector<2, int>::Left());

                    neighbours[1][1] = this;

                    //Compare
                    for (int x = 0; x < 3; x++) {
                        for (int y = 0; y < 3; y++) {
                            switch (neighbours[x][y]->state) {
                                case 0:
                                    break;
                                case 1:
                                    break;
                                case 2:
                                    break;
                                case 3:
                                    break;
                                case 4:
                                    break;
                                case 5:
                                    break;
                                case 6:
                                    break;
                                case 7:
                                    break;
                                case 8:
                                    break;
                                default:
                                    break;
                            }
                        }
                    }

                    //Dealloc
                    for (int x = 0; x < 3; x++) {
                        for (int y = 0; y < 3; y++) {
                            delete neighbours[x][y];
                        }
                    }
                }
            };
        }
    }
}

#endif //DIVISIONCORE_TILE_H
