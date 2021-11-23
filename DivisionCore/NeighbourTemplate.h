/**
  * @file NeighbourTemplate.h
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
#ifndef DIVISIONCORE_NEIGHBOURTEMPLATE_H
#define DIVISIONCORE_NEIGHBOURTEMPLATE_H

#include <memory>

using std::weak_ptr;
using std::shared_ptr;
using std::unique_ptr;

namespace DivisionCore {
    namespace Core {
        namespace Tilemaps {

            template<typename T>
            struct NeighbourTemplate {
            private:
                std::weak_ptr<T> neighbours[3][3];
            public:
                NeighbourTemplate() = default;

                explicit NeighbourTemplate(const weak_ptr<T> &clone) {
                    for (unsigned x = 0; x < 3; x++) {
                        for (unsigned y = 0; y < 3; y++) {
                            neighbours[x][y] = clone[x][y];
                        }
                    }
                }

                inline weak_ptr<T> &operator()(unsigned row, unsigned col) {
                    return neighbours[row][col];
                }

                inline weak_ptr<T> operator()(unsigned row, unsigned col) const {
                    return neighbours[row][col];
                }

                inline shared_ptr<T> GetCenter() const {
                    return neighbours[1][1].lock();
                }

                inline shared_ptr<T> GetLeftTopCorner() const {
                    return neighbours[0][2].lock();
                }

                inline shared_ptr<T> GetTop() const {
                    return neighbours[1][2].lock();
                }

                inline shared_ptr<T> GetRightTopCorner() const {
                    return neighbours[2][2].lock();
                }

                inline shared_ptr<T> GetLeft() const {
                    return neighbours[0][1].lock();
                }

                inline shared_ptr<T> GetRight() const {
                    return neighbours[2][1].lock();
                }

                inline shared_ptr<T> GetLeftDownCorner() const {
                    return neighbours[0][0].lock();
                }

                inline shared_ptr<T> GetDown() const {
                    return neighbours[1][0].lock();
                }

                inline shared_ptr<T> GetRightDownCorner() const {
                    return neighbours[2][0].lock();
                }

                constexpr static int NeighboursFactorial = 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2;
            };
        }
    }
}
#endif //DIVISIONCORE_NEIGHBOURTEMPLATE_H
