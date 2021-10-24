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
#include <algorithm>
#include <iostream>
#include <cstdint>
#include <string>
#include <list>
#include <iterator>
#include <tuple>
#include <map>

namespace DivisionCore
{
    enum class HideFlags
    {
        HIDDEN = 0,
        VISIBLE = 1
    };

    using std::string;
    using std::map;
    using std::pair;
    using std::tie;

    template <typename T> class Object
    {
        typedef uint8_t byte;
        typedef uint_least8_t dynamic_byte;
    private:
        static map<dynamic_byte, Object> idInstanceDictionary;

        static map<HideFlags, string> hideFlagsLookupTable;

        dynamic_byte instanceID;
    public:
        HideFlags hideFlags;
        string name;

        Object() {
            if (hideFlagsLookupTable.empty())
            {
                hideFlagsLookupTable.insert(std::make_pair(HideFlags::VISIBLE, "Visible"));
            }

            if (idInstanceDictionary.empty())
            {
                instanceID = 0;

                name = "Object" + instanceID;
                hideFlags = HideFlags::VISIBLE;

                idInstanceDictionary.insert(std::make_pair(instanceID, *this));
            }
            else
            {
                dynamic_byte counter = 0;

                typename map<dynamic_byte ,Object>::iterator it;
                for (it = idInstanceDictionary.begin(); it != idInstanceDictionary.end(); ++it)
                {
                    if (&(it->first) == nullptr)
                    {
                        instanceID = counter;

                        name = "Object" + instanceID;
                        hideFlags = HideFlags::VISIBLE;

                        idInstanceDictionary.insert(std::make_pair(instanceID, *this));
                    }
                    counter++;
                }
            }
        }
        ~Object()
        {
            idInstanceDictionary.erase(instanceID);
        }

        inline bool operator - () const
        {
            return this != nullptr;
        }
        inline bool operator ! () const
        {
            return this == nullptr;
        }
        inline bool operator == (const Object& other) const
        {
            return tie(instanceID, hideFlags, name) == tie(other.instanceID, other.hideFlags, other.name);
        }
        inline bool operator != (const Object& other) const
        {
            return tie(instanceID, hideFlags, name) != tie(other.instanceID, other.hideFlags, other.name);
        }

        inline int GetInstanceID() const
        {
            return instanceID;
        }

        virtual string ToString() const
        {
            return name;
        }
        virtual inline string ToJson() const
        {
            return R"({"instanceID": ")" + std::to_string(instanceID) + "\"" +
                   R"("hideFlags": ")" + hideFlagsLookupTable.find(hideFlags)->second + "\"" +
                   R"("name": ")" + name + "\"" + "}";
        }

        static T* Instantiate(const  T& object, string& name)
        {
            if(&object != nullptr)
            {
                T* tempPtr = new T(object);
                return tempPtr;
            }
            else
            {
                return nullptr;
            }
        }
        static void Destroy(T* obj)
        {
            delete obj;
        }
        static void Destroy(T* obj, const bool isArray)
        {
            if (isArray)
            {
                delete[] obj;
            } else
            {
                delete obj;
            }
        }

        template <typename Type> static Type FindObjectOfType()
        {
            typename map<dynamic_byte ,Object>::iterator it;
            for (it = idInstanceDictionary.begin(); it != idInstanceDictionary.end(); ++it)
            {
                if (dynamic_cast<Type*>(it->second) != nullptr)
                {
                    return it->second;
                }
            }
            return nullptr;
        }
        template <typename Type> static void ExpandAddArray(Type * original, const uint_least8_t size, const uint_least8_t newSize, const Type * add)
        {
            // Dealloc
            Type* temp = new Type[newSize];

            if (original != nullptr)
            {
                std::copy(original, original + size - 1, temp);
                delete [] original;
            }

            original = temp;
            original[size] = add;
        }
        template <typename Type> static Type* FindObjectsOfType()
        {
            Type* tempArr = nullptr;
            dynamic_byte counter = 0;

            typename map<dynamic_byte ,Object>::iterator it;
            for (it = idInstanceDictionary.begin(); it != idInstanceDictionary.end(); ++it)
            {
                if (dynamic_cast<Type*>(it->second) != nullptr)
                {
                    ExpandAddArray(tempArr, counter, counter + 1, it->second);
                    counter++;
                }
            }

            return tempArr;
        }

        /*static T* DontDestroyOnLoad()
        {
            T* instance = new T(This());
            return instance;
        }*/
    };
}
#endif //DIVISIONCORE_OBJECT_H


