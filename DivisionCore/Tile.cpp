/**
  * @file Tile.cpp
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

#include "ObjectMacros.h"
#include "Tile.h"
#include "Tilemap.h"
#include "Dictionary.h"

INCLUDE_OBJECT_STATIC

namespace DivisionCore {
    namespace Core {
        namespace Tilemaps {
            Tile::Tile(const Tile &clone) {
                if (&clone != this) {
                    state = clone.state;
                    if (clone.tilemap->lenght == 0) {
                        tilemap->lenght = 1.;
                    } else {
                        tilemap->lenght = clone.tilemap->lenght;
                    }

                    tilemap.reset(clone.tilemap.get());

                    for (unsigned x = 0; x < 3; x++) {
                        for (unsigned y = 0; y < 3; y++) {
                            neighbours(x, y) = clone.neighbours(x, y);
                        }
                    }

                    position = clone.position;
                    worldPosition = clone.worldPosition;
                } else {
                    if (tilemap->lenght == 0) {
                        tilemap->lenght = 1.;
                    }

                    position = Vectors::Vector2Int::Zero();
                    worldPosition = Vector2(position.coords[0] * tilemap->lenght, position.coords[0] * tilemap->lenght);

                    state = 0;

                    tilemap->grid.Add(VectorKeyValuePair<Vector, Tile *, 2, int>(position, this));
                }

                UpdateCycle();
            }

            Tile::Tile(const Tile *clone) {
                if (clone != this) {
                    state = clone->state;
                    if (clone->tilemap->lenght == 0) {
                        tilemap->lenght = 1.;
                    } else {
                        tilemap->lenght = clone->tilemap->lenght;
                    }
                    tilemap.reset(clone->tilemap.get());

                    for (unsigned x = 0; x < 3; x++) {
                        for (unsigned y = 0; y < 3; y++) {
                            neighbours(x, y) = clone->neighbours(x, y);
                        }
                    }

                    position = clone->position;
                    worldPosition = clone->worldPosition;
                } else {
                    if (tilemap->lenght == 0) {
                        tilemap->lenght = 1.;
                    }

                    position = Vectors::Vector2Int::Zero();
                    worldPosition = Vector2(position.coords[0] * tilemap->lenght, position.coords[0] * tilemap->lenght);

                    state = 0;

                    tilemap->grid.Add(VectorKeyValuePair<Vector, Tile *, 2, int>(position, this));
                }

                UpdateCycle();
            }

            Tile::Tile(const Vector2Int &_position, Tilemap &_tilemap) {
                if (tilemap->lenght == 0) {
                    tilemap->lenght = 1.;
                }

                position = _position;
                worldPosition = Vector2(_position.coords[0] * tilemap->lenght, _position.coords[0] * tilemap->lenght);

                state = 0;

                tilemap.reset(&_tilemap);
                tilemap->grid.Add(VectorKeyValuePair<Vector, Tile *, 2, int>(position, this));

                UpdateCycle();
            }

            Tile::Tile(const unique_ptr<Vector2Int> _position, Tilemap &_tilemap) {
                if (tilemap->lenght == 0) {
                    tilemap->lenght = 1.;
                }

#pragma warning (disable : 4068 ) /* Disable unknown pragma warnings */
#pragma clang diagnostic push /* Disable CLANG ide LocalValueEscapesScope warning */
#pragma ide diagnostic ignored "LocalValueEscapesScope"
                position = *_position;
#pragma clang diagnostic pop

                worldPosition = Vector2(_position->coords[0] * tilemap->lenght, _position->coords[0] * tilemap->lenght);

                state = 0;

                tilemap.reset(&_tilemap);
                tilemap->grid.Add(VectorKeyValuePair<Vector, Tile *, 2, int>(position, this));

                UpdateCycle();
            }

            Tile::Tile(initializer_list<int> list, Tilemap &_tilemap) {
                if (tilemap->lenght == 0) {
                    tilemap->lenght = 1.;
                }

                initializer_list<int>::iterator it;
                unsigned counter = 0;

                for (it = list.begin(); it < list.end(); ++it) {
                    position.coords[counter] = *it;
                    counter++;
                }

                worldPosition = Vector2(position.coords[0] * tilemap->lenght, position.coords[1] * tilemap->lenght);

                state = 0;

                tilemap.reset(&_tilemap);
                tilemap->grid.Add(VectorKeyValuePair<Vector, Tile *, 2, int>(position, this));

                UpdateCycle();
            }

            Tile::~Tile() {
                tilemap->grid.Remove(position);
                UpdateNeighbours(neighbours);
            }

            Tile &Tile::operator()(const int row, const int column) {
                return *(tilemap->GetTileAs(Vectors::Vector2Int(row, column)));
            }

            Tile *Tile::operator()(const int row, const int column) const {
                return tilemap->GetTileAs(Vectors::Vector2Int(row, column));
            }

            bool Tile::GetNeighbours() {
                if (!tilemap->grid.empty()) {
                    //Up-Midle
                    neighbours.GetTop().reset(tilemap->GetTileAs(position + Vector2Int::Up()));
                    //Down-Midle
                    neighbours.GetDown().reset(tilemap->GetTileAs(position + Vector2Int::Down()));
                    //Left-Midle
                    neighbours.GetLeft().reset(tilemap->GetTileAs(position + Vector2Int::Left()));
                    //Right-Midle
                    neighbours.GetRight().reset(tilemap->GetTileAs(position + Vector2Int::Right()));

                    //Right-up
                    neighbours.GetRightTopCorner().reset(
                            tilemap->GetTileAs(position + Vector2Int::Up() + Vector2Int::Right()));
                    //Left-Up
                    neighbours.GetLeftTopCorner().reset(
                            tilemap->GetTileAs(position + Vector2Int::Up() + Vector2Int::Left()));
                    //Right-Down
                    neighbours.GetRightDownCorner().reset(
                            tilemap->GetTileAs(position + Vector2Int::Down() + Vector2Int::Right()));
                    //Left-Down
                    neighbours.GetLeftDownCorner().reset(tilemap->GetTileAs(position + Vector2Int::Left()));

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

            bool Tile::UpdateNeighbours(const NeighbourTemplate<Tile> &filteredNeighbours) {
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
            Tile::FilterNeighboursToUpdate(const NeighbourTemplate<Tile> &other) const {

                NeighbourTemplate<Tile> filteredNeighbours;

                for (unsigned x = 0; x < 3; x++) {
                    for (unsigned y = 0; y < 3; y++) {
                        auto temp = neighbours(x, y).lock() == other(x, y).lock() ? std::make_shared<Tile>(nullptr)
                                                                                  : neighbours(x, y);
                        filteredNeighbours(x, y) = temp;
                    }
                }

                return filteredNeighbours;
            }

            unsigned Tile::FindTileState() const {

                unsigned tempState = 0;

                if (IsCenter()) {
                    tempState = 1;
                } else {
                    if (IsIsolated()) {
                        tempState = 2;
                    } else {
                        if (IsDownEnd()) {

                        } else if (IsUpEnd()) {

                        } else if (IsLeftEnd()) {

                        } else if (IsRightEnd()) {

                        } else {

                        }
                    }
                }

                return tempState;
            }

            bool Tile::UpdateCycle() {
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

            bool Tile::UpdateCycle(const NeighbourTemplate<Tile> &_neighbours) {
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
        }
    }
}

