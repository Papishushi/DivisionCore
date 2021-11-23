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
#include "NeighbourTemplate.h"

#include <memory>

using DivisionCore::Vectors::Vector;
using DivisionCore::Vectors::Vector2;
using DivisionCore::Vectors::Vector2Int;
using DivisionCore::Core::EventHandling::EventObserver;
using DivisionCore::Containers::VectorKeyValuePair;
using DivisionCore::Containers::VectorKeyDictionary;

using std::weak_ptr;
using std::shared_ptr;
using std::unique_ptr;

using std::initializer_list;

namespace DivisionCore {
    namespace Core {
        namespace Tilemaps {

            struct Tile : public Object<Tile> {
            private:
                unsigned state;
                NeighbourTemplate<Tile> neighbours;

                static float lenght;
                static Containers::VectorKeyDictionary<Vector, Tile *, 2, int> tileGrid;

                //region States
                virtual inline const bool IsCenter() const {
                    return neighbours.GetTop() && neighbours.GetDown() &&
                           neighbours.GetLeft() && neighbours.GetRight();
                }

                virtual inline const bool IsIsolated() const {
                    return !neighbours.GetTop() && !neighbours.GetDown() &&
                           !neighbours.GetLeft() && !neighbours.GetRight();
                }

                virtual inline const bool IsDownEnd() const {
                    return neighbours.GetTop() && !neighbours.GetDown() &&
                           !neighbours.GetLeft() && !neighbours.GetRight();
                }

                virtual inline const bool IsUpEnd() const {
                    return !neighbours.GetTop() && neighbours.GetDown() &&
                           !neighbours.GetLeft() && !neighbours.GetRight();
                }

                virtual inline const bool IsRightEnd() const {
                    return !neighbours.GetTop() && !neighbours.GetDown() &&
                           neighbours.GetLeft() && !neighbours.GetRight();
                }

                virtual inline const bool IsLeftEnd() const {
                    return !neighbours.GetTop() && !neighbours.GetDown() &&
                           !neighbours.GetLeft() && neighbours.GetRight();
                }
                //endregion

            protected:
                //region Neighbours exploration tools
                inline bool GetNeighbours() {
                    if (!tileGrid.empty()) {
                        //Up-Midle
                        neighbours.GetTop().reset(*tileGrid.FindValue(position + Vector2Int::Up()));
                        //Down-Midle
                        neighbours.GetDown().reset(*tileGrid.FindValue(position + Vector2Int::Down()));
                        //Left-Midle
                        neighbours.GetLeft().reset(*tileGrid.FindValue(position + Vector2Int::Left()));
                        //Right-Midle
                        neighbours.GetRight().reset(*tileGrid.FindValue(position + Vector2Int::Right()));

                        //Right-up
                        neighbours.GetRightTopCorner().reset(*tileGrid.FindValue(position + Vector2Int::Up() + Vector2Int::Right()));
                        //Left-Up
                        neighbours.GetLeftTopCorner().reset(*tileGrid.FindValue(position + Vector2Int::Up() + Vector2Int::Left()));
                        //Right-Down
                        neighbours.GetRightDownCorner().reset(*tileGrid.FindValue(position + Vector2Int::Down() + Vector2Int::Right()));
                        //Left-Down
                        neighbours.GetLeftDownCorner().reset(*tileGrid.FindValue(position + Vector2Int::Left()));

                        //Center
                        neighbours.GetCenter().reset(std::make_shared<Tile>(this).get());
                        return true;
                    } else {
                        return false;
                    }

                    /*1 2 3
                      4 0 5
                      6 7 8*/
                }

                bool UpdateNeighbours(const NeighbourTemplate<Tile>& filteredNeighbours) {
                    /*1 2 3
                      4 0 5
                      6 7 8*/

                    bool returnValue = true;

                    //Up-Midle
                    if (filteredNeighbours.GetTop()) {
                        if (!filteredNeighbours.GetTop()->UpdateCycle(neighbours)) {
                            returnValue = false;
                        }
                    }

                    //Down-Midle
                    if (filteredNeighbours.GetDown()) {
                        if (!filteredNeighbours.GetDown()->UpdateCycle(neighbours)) {
                            returnValue = false;
                        }
                    }

                    //Left-Midle
                    if (!filteredNeighbours.GetLeft() ||
                        !filteredNeighbours.GetLeft()->UpdateCycle(neighbours)) {
                        returnValue = false;
                    }

                    //Right-Midle
                    if (!filteredNeighbours.GetRight() ||
                        !filteredNeighbours.GetRight()->UpdateCycle(neighbours)) {
                        returnValue = false;
                    }

                    //Right-up
                    if (!filteredNeighbours.GetRightTopCorner() ||
                        !filteredNeighbours.GetRightTopCorner()->UpdateCycle(neighbours)) {
                        returnValue = false;
                    }

                    //Left-Up
                    if (!filteredNeighbours.GetLeftTopCorner() ||
                        !filteredNeighbours.GetLeftTopCorner()->UpdateCycle(neighbours)) {
                        returnValue = false;
                    }

                    //Right-Down
                    if (!filteredNeighbours.GetRightDownCorner() ||
                        !filteredNeighbours.GetRightDownCorner()->UpdateCycle(neighbours)) {
                        returnValue = false;
                    }

                    //Left-Down
                    if (!filteredNeighbours.GetLeftDownCorner() ||
                        !filteredNeighbours.GetLeftDownCorner()->UpdateCycle(neighbours)) {
                        returnValue = false;
                    }

                    return returnValue;
                }

                NeighbourTemplate<Tile>
                FilterNeighboursToUpdate(const NeighbourTemplate<Tile>& other) const {

                    NeighbourTemplate<Tile> filteredNeighbours;

                    for (unsigned x = 0; x < 3; x++) {
                        for (unsigned y = 0; y < 3; y++) {
                            auto temp = neighbours(x,y).lock() == other(x,y).lock() ? std::make_shared<Tile>(nullptr)
                                                                                      : neighbours(x,y);
                            filteredNeighbours(x,y) = temp;
                        }
                    }

                    return filteredNeighbours;
                }

                unsigned FindTileState() const {
                    return 0;
                }
                //endregion
            public:
                Vector2Int position;
                Vector2 worldPosition;

                //region Constructors & Destructor
                Tile() = delete;

                explicit Tile(const Tile &clone) {
                    if (&clone != this) {
                        this->state = clone.state;
                        if (clone.lenght == 0) {
                            this->lenght = 1.;
                        } else {
                            this->lenght = clone.lenght;
                        }
                        this->tileGrid = clone.tileGrid;

                        for (unsigned x = 0; x < 3; x++) {
                            for (unsigned y = 0; y < 3; y++) {
                                this->neighbours(x,y) = clone.neighbours(x,y);
                            }
                        }

                        this->position = clone.position;
                        this->worldPosition = clone.worldPosition;
                    } else {
                        if (lenght == 0) {
                            lenght = 1.;
                        }

                        position = Vectors::Vector2Int::Zero();
                        worldPosition = Vector2(position.coords[0] * lenght, position.coords[0] * lenght);

                        state = 0;

                        tileGrid.Add(VectorKeyValuePair<Vector, Tile *, 2, int>(position, this));
                    }

                    UpdateCycle();
                }

                explicit Tile(const Tile *clone) {
                    if (clone != this) {
                        this->state = clone->state;
                        if (clone->lenght == 0) {
                            this->lenght = 1.;
                        } else {
                            this->lenght = clone->lenght;
                        }
                        this->tileGrid = clone->tileGrid;

                        for (unsigned x = 0; x < 3; x++) {
                            for (unsigned y = 0; y < 3; y++) {
                                this->neighbours(x,y) = clone->neighbours(x,y);
                            }
                        }

                        this->position = clone->position;
                        this->worldPosition = clone->worldPosition;
                    } else {
                        if (lenght == 0) {
                            lenght = 1.;
                        }

                        position = Vectors::Vector2Int::Zero();
                        worldPosition = Vector2(position.coords[0] * lenght, position.coords[0] * lenght);

                        state = 0;

                        tileGrid.Add(VectorKeyValuePair<Vector, Tile *, 2, int>(position, this));
                    }

                    UpdateCycle();
                }

                explicit Tile(const Vector2Int &_position) {
                    if (lenght == 0) {
                        lenght = 1.;
                    }

                    position = _position;
                    worldPosition = Vector2(_position.coords[0] * lenght, _position.coords[0] * lenght);

                    state = 0;

                    tileGrid.Add(VectorKeyValuePair<Vector, Tile *, 2, int>(position, this));

                    UpdateCycle();
                }

                explicit Tile(const unique_ptr<Vector2Int> _position) {
                    if (lenght == 0) {
                        lenght = 1.;
                    }

#pragma warning (disable : 4068 ) /* Disable unknown pragma warnings */
#pragma clang diagnostic push /* Disable CLANG ide LocalValueEscapesScope warning */
#pragma ide diagnostic ignored "LocalValueEscapesScope"
                    position = *_position;
#pragma clang diagnostic pop

                    worldPosition = Vector2(_position->coords[0] * lenght, _position->coords[0] * lenght);

                    state = 0;

                    tileGrid.Add(VectorKeyValuePair<Vector, Tile *, 2, int>(position, this));

                    UpdateCycle();
                }

                explicit Tile(initializer_list<int> list) {
                    if (lenght == 0) {
                        lenght = 1.;
                    }

                    initializer_list<int>::iterator it;
                    unsigned counter = 0;

                    for (it = list.begin(); it < list.end(); ++it) {
                        position.coords[counter] = *it;
                        counter++;
                    }

                    worldPosition = Vector2(position.coords[0] * lenght, position.coords[1] * lenght);

                    state = 0;

                    tileGrid.Add(VectorKeyValuePair<Vector, Tile *, 2, int>(position, this));

                    UpdateCycle();
                }

                virtual ~Tile() {
                    tileGrid.Remove(position);
                    UpdateNeighbours(neighbours);
                }
                //endregion

                bool UpdateCycle() {
                    /*1 2 3
                      4 0 5
                      6 7 8*/
                    if (GetNeighbours()) {
                        if (UpdateNeighbours(neighbours)) {
                            state = FindTileState();
                            return true;
                        } else {
                            return false;
                        }
                    } else {
                        return false;
                    }
                }

                bool UpdateCycle(const NeighbourTemplate<Tile>& _neighbours) {
                    /*1 2 3
                      4 0 5
                      6 7 8*/
                    if (GetNeighbours()) {
                        if (UpdateNeighbours(FilterNeighboursToUpdate(_neighbours))) {
                            state = FindTileState();
                            return true;
                        } else {
                            return false;
                        }
                    } else {
                        return false;
                    }

                }

                inline const unsigned &getState() const {
                    return state;
                }
            };
        }
    }
}

#endif //DIVISIONCORE_TILE_H
