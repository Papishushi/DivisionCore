/**
  * @file ObjectMacros.h
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
#ifndef DIVISIONCORE_OBJECTMACROS_H
#define DIVISIONCORE_OBJECTMACROS_H

#include "Object.h"

using namespace DivisionCore::Core;

using DivisionCore::Containers::TemplateValueDictionary;
using DivisionCore::Containers::Dictionary;

namespace DivisionCore {
    namespace Core {
        #define Macro_ObjectStaticA template<typename T> TemplateValueDictionary<typename Object<T>::dynamic_byte, Object, T> Object<T>::idInstanceDictionary;
        #define Macro_ObjectStaticB template<typename T> Dictionary<typename Object<T>::dynamic_byte, string> Object<T>::hideFlagsLookupTable;
        #define Macro_ObjectStaticC template<typename T> unsigned char Object<T>::lastInstanceId;

        #define INCLUDE_OBJECT_STATIC Macro_ObjectStaticA \
                                      Macro_ObjectStaticB \
                                      Macro_ObjectStaticC

    }
}

#endif //DIVISIONCORE_OBJECTMACROS_H
