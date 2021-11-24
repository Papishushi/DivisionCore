/**
  * @file Tilemap.h
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
#ifndef DIVISIONCORE_TILEMAP_H
#define DIVISIONCORE_TILEMAP_H

#include "Vector.h"
#include "RunningBehaviour.h"
#include "Dictionary.h"
#include "Tile.h"

#include <memory>

using DivisionCore::Vectors::Vector;
using DivisionCore::Vectors::Vector2Int;
using DivisionCore::Containers::VectorKeyDictionary;

using std::shared_ptr;

namespace DivisionCore {
    namespace Core {
        namespace Tilemaps {
            class Tilemap : public RunningBehaviour {
            public:
                VectorKeyDictionary<Vector, Tile *, 2, int> grid;
                float lenght;

                template<typename T = Tile>
                T GetTileAs(const shared_ptr<Tile> &tile) {
                    return dynamic_cast<T>(tile.get());
                }

                template<typename T = Tile>
                T *GetTileAs(const Vector2Int &key) {
                    return dynamic_cast<T *>(*grid.FindValue(key));
                }

                inline Tile &operator()(const int row, const int col) {
                    return *(*grid.FindValue(Vectors::Vector2Int(row, col)));
                }

                inline Tile *operator()(const int row, const int col) const {
                    return *grid.FindValue(Vectors::Vector2Int(row, col));
                }
            };
        }
    }
}

#endif //DIVISIONCORE_TILEMAP_H
