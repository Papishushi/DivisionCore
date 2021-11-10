/**
  * @file Random.h
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
#ifndef DIVISIONCORE_RANDOM_H
#define DIVISIONCORE_RANDOM_H
#include "Vector.h"
#include <ctime>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <array>


using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::chrono::system_clock;

namespace DivisionCore { namespace Core {
        class Random final {
        public:

            Random() = delete;

            ~Random() = delete;

            static unsigned GetStdChronoNanoUnits() {
                auto input = duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();

                unsigned units, decenes, centenes,
                        unitsT, decenesT, centenesT,
                        unitsM, decenesM, centenesM,
                        unitsB, decenesB, centenesB,
                        unitsTR, decenesTR, centenesTR,
                        unitsC, decenesC, centenesC,
                        unitsQ;

                unitsQ = input * 0.000000000000000001;

                centenesC = (input - (unitsQ * 1000000000000000000)) * 0.00000000000000001;

                decenesC =
                        (input - (centenesC * 100000000000000000 + unitsQ * 1000000000000000000)) * 0.0000000000000001;

                unitsC = (input - (decenesC * 1000000000000000 + centenesC * 100000000000000000 +
                                   unitsQ * 1000000000000000000)) * 0.000000000000001;

                centenesTR = (input - (unitsC * 1000000000000000 + decenesC * 1000000000000000 +
                                       centenesC * 100000000000000000 +
                                       unitsQ * 1000000000000000000)) * 0.00000000000001;

                decenesTR = (input -
                             (centenesTR * 100000000000000 + unitsC * 1000000000000000 + decenesC * 1000000000000000 +
                              centenesC * 100000000000000000 + unitsQ * 1000000000000000000)) * 0.0000000000001;

                unitsTR = (input -
                           (decenesTR * 10000000000000 + centenesTR * 100000000000000 + unitsC * 1000000000000000 +
                            decenesC * 1000000000000000 + centenesC * 100000000000000000 +
                            unitsQ * 1000000000000000000)) * 0.000000000001;

                centenesB =
                        (input - (unitsTR * 1000000000000 + decenesTR * 10000000000000 + centenesTR * 100000000000000 +
                                  unitsC * 1000000000000000 + decenesC * 1000000000000000 +
                                  centenesC * 100000000000000000 +
                                  unitsQ * 1000000000000000000)) * 0.00000000001;

                decenesB = (input - (centenesB * 100000000000 + unitsTR * 1000000000000 + decenesTR * 10000000000000 +
                                     centenesTR * 100000000000000 + unitsC * 1000000000000000 +
                                     decenesC * 1000000000000000 +
                                     centenesC * 100000000000000000 + unitsQ * 1000000000000000000)) * 0.0000000001;

                unitsB = (input - (decenesB * 10000000000 + centenesB * 100000000000 + unitsTR * 1000000000000 +
                                   decenesTR * 10000000000000 + centenesTR * 100000000000000 +
                                   unitsC * 1000000000000000 +
                                   decenesC * 1000000000000000 + centenesC * 100000000000000000 +
                                   unitsQ * 1000000000000000000)) * 0.000000001;

                centenesM = (input - (unitsB * 1000000000 + decenesB * 10000000000 + centenesB * 100000000000 +
                                      unitsTR * 1000000000000 + decenesTR * 10000000000000 +
                                      centenesTR * 100000000000000 +
                                      unitsC * 1000000000000000 + decenesC * 1000000000000000 +
                                      centenesC * 100000000000000000 +
                                      unitsQ * 1000000000000000000)) * 0.00000001;

                decenesM = (input - (centenesM * 100000000 + unitsB * 1000000000 + decenesB * 10000000000 +
                                     centenesB * 100000000000 + unitsTR * 1000000000000 + decenesTR * 10000000000000 +
                                     centenesTR * 100000000000000 + unitsC * 1000000000000000 +
                                     decenesC * 1000000000000000 +
                                     centenesC * 100000000000000000 + unitsQ * 1000000000000000000)) * 0.0000001;

                unitsM = (input - (decenesM * 10000000 + centenesM * 100000000 + unitsB * 1000000000 +
                                   decenesB * 10000000000 + centenesB * 100000000000 + unitsTR * 1000000000000 +
                                   decenesTR * 10000000000000 + centenesTR * 100000000000000 +
                                   unitsC * 1000000000000000 +
                                   decenesC * 1000000000000000 + centenesC * 100000000000000000 +
                                   unitsQ * 1000000000000000000)) * 0.000001;

                centenesT = (input - (unitsM * 1000000 + decenesM * 10000000 + centenesM * 100000000 +
                                      unitsB * 1000000000 + decenesB * 10000000000 + centenesB * 100000000000 +
                                      unitsTR * 1000000000000 + decenesTR * 10000000000000 +
                                      centenesTR * 100000000000000 +
                                      unitsC * 1000000000000000 + decenesC * 1000000000000000 +
                                      centenesC * 100000000000000000 +
                                      unitsQ * 1000000000000000000)) * 0.00001;

                decenesT = (input - (centenesT * 100000 + unitsM * 1000000 + decenesM * 10000000 +
                                     centenesM * 100000000 + unitsB * 1000000000 + decenesB * 10000000000 +
                                     centenesB * 100000000000 + unitsTR * 1000000000000 + decenesTR * 10000000000000 +
                                     centenesTR * 100000000000000 + unitsC * 1000000000000000 +
                                     decenesC * 1000000000000000 +
                                     centenesC * 100000000000000000 + unitsQ * 1000000000000000000)) * 0.0001;

                unitsT = (input - (decenesT * 10000 + centenesT * 100000 + unitsM * 1000000 +
                                   decenesM * 10000000 + centenesM * 100000000 + unitsB * 1000000000 +
                                   decenesB * 10000000000 + centenesB * 100000000000 + unitsTR * 1000000000000 +
                                   decenesTR * 10000000000000 + centenesTR * 100000000000000 +
                                   unitsC * 1000000000000000 +
                                   decenesC * 1000000000000000 + centenesC * 100000000000000000 +
                                   unitsQ * 1000000000000000000)) * 0.001;

                centenes = (input - (unitsT * 1000 + decenesT * 10000 + centenesT * 100000 +
                                     unitsM * 1000000 + decenesM * 10000000 + centenesM * 100000000 +
                                     unitsB * 1000000000 + decenesB * 10000000000 + centenesB * 100000000000 +
                                     unitsTR * 1000000000000 + decenesTR * 10000000000000 +
                                     centenesTR * 100000000000000 +
                                     unitsC * 1000000000000000 + decenesC * 1000000000000000 +
                                     centenesC * 100000000000000000 + unitsQ * 1000000000000000000)) * 0.01;

                decenes = (input - (centenes * 100 + unitsT * 1000 + decenesT * 10000 +
                                    centenesT * 100000 + unitsM * 1000000 + decenesM * 10000000 +
                                    centenesM * 100000000 + unitsB * 1000000000 + decenesB * 10000000000 +
                                    centenesB * 100000000000 + unitsTR * 1000000000000 + decenesTR * 10000000000000 +
                                    centenesTR * 100000000000000 + unitsC * 1000000000000000 +
                                    decenesC * 1000000000000000 +
                                    centenesC * 100000000000000000 + unitsQ * 1000000000000000000)) * 0.1;

                units = (input - (decenes * 10 + centenes * 100 + unitsT * 1000 +
                                  decenesT * 10000 + centenesT * 100000 + unitsM * 1000000 +
                                  decenesM * 10000000 + centenesM * 100000000 + unitsB * 1000000000 +
                                  decenesB * 10000000000 + centenesB * 100000000000 + unitsTR * 1000000000000 +
                                  decenesTR * 10000000000000 + centenesTR * 100000000000000 +
                                  unitsC * 1000000000000000 +
                                  decenesC * 1000000000000000 + centenesC * 100000000000000000 +
                                  unitsQ * 1000000000000000000));

                return units;
            }
            static double Value() {
                const static float seed = 0.2;
                const static unsigned delta = 4;

                double random = seed;
                unsigned units = GetStdChronoNanoUnits();

                for (unsigned i = 0; i < units * 2; i++) {
                    random = random * delta * (1 - random);
                }

                units = GetStdChronoNanoUnits();

                if (units == 0) {
                    units = 1;
                }

                return random * units * (0.5 - (random * 0.5)) * (1 - random);
            }
            static float PerlinNoise(Vectors::Vector2 position)
            {
                struct GradientGrid
                {
                   Vectors::Vector2 grid [340282346638528859811704183484516925440 * 2][340282346638528859811704183484516925440 * 2];
                   long float gridSize = 340282346638528859811704183484516925440 * 4;

                   GradientGrid()
                   {
                       for(int x = 0; x < gridSize * 0.5; x++)
                       {
                           for(int y = 0; x < gridSize * 0.5; x++)
                           {
                                grid[x][y] = Vectors::Vector2::One() * Value();
                           }
                       }
                   }
                   
                };

                GradientGrid gradientGrid = GradientGrid();

                if(position.x)
                {

                }
                if(position.y)
                {

                }
            }
        };
    }}
#endif //DIVISIONCORE_RANDOM_H
