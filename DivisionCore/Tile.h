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

                virtual inline const unsigned &getState() const {
                    return state;
                }

                virtual void CompareNeighbours() {
                    //Alloc
                    Tile *neighbours[3][3];

                    //Up-Midle
                    neighbours[1][2] = *tileGrid.FindValue(position + Vector<2, int>::Up());
                    //Down-Midle
                    neighbours[1][0] = *tileGrid.FindValue(position + Vector<2, int>::Down());
                    //Left-Midle
                    neighbours[0][1] = *tileGrid.FindValue(position + Vector<2, int>::Left());
                    //Right-Midle
                    neighbours[2][1] = *tileGrid.FindValue(position + Vector<2, int>::Right());

                    //Right-up
                    neighbours[2][2] = *tileGrid.FindValue(position + Vector<2, int>::Up() + Vector<2, int>::Right());
                    //Left-Up
                    neighbours[0][2] = *tileGrid.FindValue(position + Vector<2, int>::Up() + Vector<2, int>::Left());
                    //Right-Down
                    neighbours[2][0] = *tileGrid.FindValue(position + Vector<2, int>::Down() + Vector<2, int>::Right());
                    //Left-Down
                    neighbours[0][0] = *tileGrid.FindValue(position + Vector<2, int>::Left());

                    //Center
                    neighbours[1][1] = this;


                    /*1 2 3
                      4 0 5
                      6 7 8*/
                    //If 5 or more of this states match update State
                    unsigned proposedStates[9] = {0,0,0,0,0,0,0,0,0};
                    unsigned index = 0;

                    if(neighbours[1][1] == nullptr){

                    } else {
                        //Compare & vote 9 iterations
                        for (unsigned x = 0; x < 3; x++) {
                            for (unsigned y = 0; y < 3; y++) {
                                if(neighbours[x][y] != nullptr)
                                {
                                    switch (neighbours[x][y]->getState()) {
                                        //State
                                        case 0:

                                            break;
                                            //State
                                        case 1:

                                            break;
                                            //State
                                        case 2:

                                            break;
                                            //State
                                        case 3:

                                            break;
                                            //State
                                        case 4:

                                            break;
                                            //State
                                        case 5:

                                            break;
                                            //State
                                        case 6:

                                            break;
                                            //State
                                        case 7:

                                            break;
                                            //State
                                        case 8:

                                            break;
                                            //State
                                        default:
                                            //Relative position (Not done)
                                            switch (x) {
                                                case 0:
                                                    switch (y) {
                                                        case 0:
                                                            proposedStates[index] = 0;
                                                            break;
                                                        case 1:
                                                            proposedStates[index] = 0;
                                                            break;
                                                        case 2:
                                                            proposedStates[index] = 0;
                                                            break;
                                                        default:
                                                            proposedStates[index] = 0;
                                                            break;
                                                    }
                                                    break;
                                                case 1:
                                                    switch (y) {
                                                        case 0:
                                                            proposedStates[index] = 0;
                                                            break;
                                                        case 2:
                                                            proposedStates[index] = 0;
                                                            break;
                                                        default:
                                                            proposedStates[index] = 0;
                                                            break;
                                                    }
                                                    break;
                                                case 2:
                                                    switch (y) {
                                                        case 0:
                                                            proposedStates[index] = 0;
                                                            break;
                                                        case 1:
                                                            proposedStates[index] = 0;
                                                            break;
                                                        case 2:
                                                            proposedStates[index] = 0;
                                                            break;
                                                        default:
                                                            proposedStates[index] = 0;
                                                            break;
                                                    }
                                                    break;
                                                default:
                                                    proposedStates[index] = 0;
                                                    break;
                                            }
                                            break;
                                    }
                                }
                                else
                                {
                                    switch (x) {
                                        case 0:
                                            switch (y) {
                                                case 0:
                                                    proposedStates[index] = 6;
                                                    break;
                                                case 1:
                                                    proposedStates[index] = 4;
                                                    break;
                                                case 2:
                                                    proposedStates[index] = 1;
                                                    break;
                                                default:
                                                    proposedStates[index] = 0;
                                                    break;
                                            }
                                            break;
                                        case 1:
                                            switch (y) {
                                                case 0:
                                                    proposedStates[index] = 7;
                                                    break;
                                                case 2:
                                                    proposedStates[index] = 2;
                                                    break;
                                                default:
                                                    proposedStates[index] = 0;
                                                    break;
                                            }
                                            break;
                                        case 2:
                                            switch (y) {
                                                case 0:
                                                    proposedStates[index] = 8;
                                                    break;
                                                case 1:
                                                    proposedStates[index] = 5;
                                                    break;
                                                case 2:
                                                    proposedStates[index] = 3;
                                                    break;
                                                default:
                                                    proposedStates[index] = 0;
                                                    break;
                                            }
                                            break;
                                        default:
                                            proposedStates[index] = 0;
                                            break;
                                    }
                                }
                                index++;
                            }
                        }
                        /*1 2 3
                          4 0 5
                          6 7 8*/
                    }



                    //Dealloc
                    for (unsigned x = 0; x < 3; x++) {
                        for (unsigned y = 0; y < 3; y++) {
                            delete neighbours[x][y];
                        }
                    }
                }
            };
        }
    }
}

#endif //DIVISIONCORE_TILE_H
