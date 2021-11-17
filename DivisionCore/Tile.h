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

#include <memory>

using DivisionCore::Vectors::Vector;
using DivisionCore::Vectors::Vector2;
using DivisionCore::Vectors::Vector2Int;
using DivisionCore::Core::EventHandling::EventObserver;
using DivisionCore::Containers::VectorKeyValuePair;
using DivisionCore::Containers::VectorKeyDictionary;

using std::weak_ptr;
using std::shared_ptr;

namespace DivisionCore {
    namespace Core {
        namespace Tilemaps {
            struct Tile : public Object<Tile>{
            private:
                unsigned state;
                static float lenght;
                static Containers::VectorKeyDictionary<Vector, Tile *, 2, int> tileGrid;

                shared_ptr<Tile> neighbours[3][3];

                //region States
                virtual inline const bool IsCenter() const
                {
                    return neighbours[1][2] != nullptr && neighbours[1][0] != nullptr && neighbours[0][1] != nullptr && neighbours[2][1] != nullptr;
                }

                virtual inline const bool IsIsolated() const
                {
                    return neighbours[1][2] == nullptr && neighbours[1][0] == nullptr && neighbours[0][1] == nullptr && neighbours[2][1] == nullptr;
                }

                virtual inline const bool IsDownEnd() const
                {
                    return neighbours[1][2] != nullptr && neighbours[1][0] == nullptr && neighbours[0][1] == nullptr && neighbours[2][1] == nullptr;
                }
                virtual inline const bool IsUpEnd() const
                {
                    return neighbours[1][2] == nullptr && neighbours[1][0] != nullptr && neighbours[0][1] == nullptr && neighbours[2][1] == nullptr;
                }
                virtual inline const bool IsRightEnd() const
                {
                    return neighbours[1][2] == nullptr && neighbours[1][0] == nullptr && neighbours[0][1] != nullptr && neighbours[2][1] == nullptr;
                }
                virtual inline const bool IsLeftEnd() const
                {
                    return neighbours[1][2] == nullptr && neighbours[1][0] == nullptr && neighbours[0][1] == nullptr && neighbours[2][1] != nullptr;
                }
                //endregion

            public:
                Vector2Int position;
                Vector2 worldPosition;

                Tile() = delete;
                explicit Tile(const Tile& clone)
                {
                    if(&clone != this)
                    {
                        this->state = clone.state;
                        this->lenght = clone.lenght;
                        this->tileGrid = clone.tileGrid;

                        for(unsigned x = 0; x < 3; x++)
                        {
                            for(unsigned y = 0; y < 3; y++)
                            {
                                this->neighbours[x][y] = clone.neighbours[x][y];
                            }
                        }

                        this->position = clone.position;
                        this->worldPosition = clone.worldPosition;
                    }
                }
                explicit Tile(const Vector2Int &_position) {
                    if (lenght == 0) {
                        lenght = 1.;
                    }

                    position = _position;
                    worldPosition = Vector2(_position.coords[0] * lenght, _position.coords[0] * lenght);

                    state = 0;

                    tileGrid.Add(VectorKeyValuePair<Vector, Tile *, 2, int>(position, this));
                }
                explicit Tile(const weak_ptr<Vector2Int> _position) {
                    if (lenght == 0) {
                        lenght = 1.;
                    }

                    std::shared_ptr<Vector2Int> sharedPtr = _position.lock();

                    position = *sharedPtr;
                    worldPosition = Vector2(sharedPtr->coords[0] * lenght, sharedPtr->coords[0] * lenght);

                    state = 0;

                    tileGrid.Add(VectorKeyValuePair<Vector, Tile *, 2, int>(position, this));
                }
                explicit Tile(std::initializer_list<int> list)
                {
                    if (lenght == 0) {
                        lenght = 1.;
                    }

                    std::initializer_list<int>::iterator it;
                    unsigned counter = 0;

                    for(it = list.begin(); it < list.end(); ++it)
                    {
                        position.coords[counter] = *it;
                        counter++;
                    }

                    worldPosition = Vector2(position.coords[0] * lenght, position.coords[0] * lenght);

                    state = 0;

                    tileGrid.Add(VectorKeyValuePair<Vector, Tile *, 2, int>(position, this));
                }
                virtual ~Tile() {
                    tileGrid.Remove(position);
                }

                virtual void UpdateCycle(){
                    /*1 2 3
                      4 0 5
                      6 7 8*/
                    GetNeighbours();
                    UpdateNeighbours();


                }
                virtual inline const unsigned &getState() const {
                    return state;
                }
                virtual void GetNeighbours() {
                    //Up-Midle
                    neighbours[1][2].reset(*tileGrid.FindValue(position + Vector2Int::Up()));
                    //Down-Midle
                    neighbours[1][0].reset(*tileGrid.FindValue(position + Vector2Int::Down()));
                    //Left-Midle
                    neighbours[0][1].reset(*tileGrid.FindValue(position + Vector2Int::Left()));
                    //Right-Midle
                    neighbours[2][1].reset(*tileGrid.FindValue(position + Vector2Int::Right()));

                    //Right-up
                    neighbours[2][2].reset(*tileGrid.FindValue(position + Vector2Int::Up() + Vector2Int::Right()));
                    //Left-Up
                    neighbours[0][2].reset(*tileGrid.FindValue(position + Vector2Int::Up() + Vector2Int::Left()));
                    //Right-Down
                    neighbours[2][0].reset(*tileGrid.FindValue(position + Vector2Int::Down() + Vector2Int::Right()));
                    //Left-Down
                    neighbours[0][0].reset(*tileGrid.FindValue(position + Vector2Int::Left()));

                    //Center
                    neighbours[1][1].reset(this);

                    /*1 2 3
                      4 0 5
                      6 7 8*/
                }
                virtual void UpdateNeighbours()
                {
                    /*1 2 3
                      4 0 5
                      6 7 8*/

                    //Up-Midle
                    neighbours[1][2]->UpdateCycle();
                    //Down-Midle
                    neighbours[1][0]->UpdateCycle();
                    //Left-Midle
                    neighbours[0][1]->UpdateCycle();
                    //Right-Midle
                    neighbours[2][1]->UpdateCycle();

                    //Right-up
                    neighbours[2][2]->UpdateCycle();
                    //Left-Up
                    neighbours[0][2]->UpdateCycle();
                    //Right-Down
                    neighbours[2][0]->UpdateCycle();
                    //Left-Down
                    neighbours[0][0]->UpdateCycle();
                }
            };
        }
    }
}

#endif //DIVISIONCORE_TILE_H
