/**
  * @file Object.h
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
#ifndef DIVISIONCORE_OBJECT_H
#define DIVISIONCORE_OBJECT_H

#include "HideFlags.h"
#include "Dictionary.h"

using DivisionCore::Containers::Dictionary;
using DivisionCore::Containers::TemplateValueDictionary;
using DivisionCore::Containers::KeyValuePair;
using DivisionCore::Containers::KeyTemplateValuePair;

#include <algorithm>
#include <iostream>
#include <cstdint>
#include <string>
#include <list>
#include <tuple>

namespace DivisionCore {
    namespace Core {
        using std::string;
        using std::tie;


        template<typename T>
        class Object {
        protected:
            typedef uint_least8_t dynamic_byte;
            static Dictionary<dynamic_byte, string> hideFlagsLookupTable;

            static TemplateValueDictionary<dynamic_byte, Object, T> idInstanceDictionary;
        private:
            dynamic_byte instanceID;
            static dynamic_byte lastInstanceId;
        public:
            HideFlags hideFlags;
            string name;

            Object() {
                if (hideFlagsLookupTable.empty()) {
                    hideFlagsLookupTable.Add(
                            KeyValuePair<dynamic_byte, string>::MakePair((dynamic_byte) HideFlags::HIDDEN, "Hidden"));
                    hideFlagsLookupTable.Add(
                            KeyValuePair<dynamic_byte, string>::MakePair((dynamic_byte) HideFlags::VISIBLE, "Visible"));
                }

                if (idInstanceDictionary.empty()) {
                    instanceID = 0;
                    lastInstanceId = instanceID;

                    name = "Object" + instanceID;
                    hideFlags = HideFlags::VISIBLE;

                    idInstanceDictionary.Add(
                            KeyTemplateValuePair<dynamic_byte, Object, T>::MakePair(instanceID, *this));
                } else {
                    instanceID = lastInstanceId + 1;
                    lastInstanceId = instanceID;

                    name = "Object" + instanceID;
                    hideFlags = HideFlags::VISIBLE;

                    idInstanceDictionary.Add(
                            KeyTemplateValuePair<dynamic_byte, Object, T>::MakePair(instanceID, *this));
                }
            }

            virtual ~Object() {
                idInstanceDictionary.Remove(instanceID);
            }

            inline bool operator-() const {
                return this != nullptr;
            }

            inline bool operator!() const {
                return this == nullptr;
            }

            inline bool operator==(const Object &other) const {
                return tie(instanceID, hideFlags, name) == tie(other.instanceID, other.hideFlags, other.name);
            }

            inline bool operator!=(const Object &other) const {
                return tie(instanceID, hideFlags, name) != tie(other.instanceID, other.hideFlags, other.name);
            }

            inline int GetInstanceID() const {
                return instanceID;
            }

            virtual string ToString() const {
                return name;
            }

            virtual inline string ToJson() const {
                return R"({"instanceID": ")" + std::to_string(instanceID) + "\"" +
                       R"("hideFlags": ")" + *hideFlagsLookupTable.FindValue((dynamic_byte) hideFlags) + "\"" +
                       R"("name": ")" + name + "\"" + "}";
            }

            static T *Instantiate(const T &object, const string &name) {
                if (&object != nullptr) {
                    T *tempPtr = new T(object);
                    return tempPtr;
                } else {
                    return nullptr;
                }
            }

            static void Destroy(T *obj) {
                delete obj;
            }

            static void Destroy(T *obj, const bool isArray) {
                if (obj != nullptr) {
                    if (isArray) {
                        delete[] obj;
                    } else {
                        delete obj;
                    }
                }
            }

            template<typename Type>
            static Type FindObjectOfType() {
                typename TemplateValueDictionary<dynamic_byte, Object, T>::iterator it;
                for (it = idInstanceDictionary.begin(); it != idInstanceDictionary.end(); ++it) {
                    if (dynamic_cast<Type *>(it.operator*()->value) != nullptr) {
                        return it.operator*()->value;
                    }
                }
                return nullptr;
            }

            template<typename Type>
            static void ExpandAddArray(Type *original, const size_t size, const size_t newSize, const Type *add) {
                // Dealloc
                Type *temp = new Type[newSize];

                if (original != nullptr) {
                    std::copy(original, original + size - 1, temp);
                    delete[] original;
                }

                original = temp;
                original[size] = add;
            }

            template<typename Type>
            static Type *FindObjectsOfType() {
                Type *tempArr = nullptr;
                dynamic_byte counter = 0;

                typename KeyTemplateValuePair<dynamic_byte, Object, T>::iterator it;
                for (it = idInstanceDictionary.begin(); it != idInstanceDictionary.end(); ++it) {
                    if (dynamic_cast<Type *>(it.operator*()->value) != nullptr) {
                        ExpandAddArray(tempArr, counter, counter + 1, it.operator*()->value);
                        counter++;
                    }
                }

                return tempArr;
            }

            /*static EmisorType* DontDestroyOnLoad()
            {
                EmisorType* instance = new EmisorType(This());
                return instance;
            }*/
        };
    }
}
#endif //DIVISIONCORE_OBJECT_H


