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

            class Tilemap;

            struct Tile : public Object<Tile> {
            private:
                unsigned state;
                NeighbourTemplate<Tile> neighbours;

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
                bool GetNeighbours();

                bool UpdateNeighbours(const NeighbourTemplate<Tile> &filteredNeighbours);

                NeighbourTemplate<Tile>
                FilterNeighboursToUpdate(const NeighbourTemplate<Tile> &other) const;

                unsigned FindTileState() const;
                //endregion
            public:
                Vector2Int position;
                Vector2 worldPosition;
                shared_ptr<Tilemap> tilemap;

                //region Constructors & Destructor
                Tile() = delete;

                explicit Tile(const Tile &clone);

                explicit Tile(const Tile *clone);

                explicit Tile(const Vector2Int &_position, Tilemap & _tilemap);

                explicit Tile(const unique_ptr<Vector2Int> _position, Tilemap & _tilemap);

                explicit Tile(initializer_list<int> list, Tilemap & _tilemap);

                virtual ~Tile();
                //endregion

                //region Operators
                inline Tile &operator()(const int row, const int column);
                inline Tile *operator()(const int row, const int column) const;
                //endregion

                inline const unsigned &getState() const {
                    return state;
                }

                bool UpdateCycle();

                bool UpdateCycle(const NeighbourTemplate<Tile> &_neighbours);
            };
        }
    }
}

#endif //DIVISIONCORE_TILE_H
