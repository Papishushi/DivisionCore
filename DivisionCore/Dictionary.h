/**
  * @file Map.h
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
#ifndef DIVISIONCORE_DICTIONARY_H
#define DIVISIONCORE_DICTIONARY_H

#include <cstdint>
#include <iterator>
#include <vector>
#include <type_traits>

using std::vector;

namespace DivisionCore { namespace Containers {
        template <typename A , typename B>
        class KeyValuePair
        {
        public:
            A * key;
            B * value;

            KeyValuePair() = delete;
            KeyValuePair(const KeyValuePair<A,B>&) = default;
            KeyValuePair(A* _key, B* _value){
                key = _key;
                value = _value;
            };
            KeyValuePair(const A& _key, const B& _value){
                key = new A(_key);
                value = new B(_value);
            };
            ~KeyValuePair()
            {
                delete key;
                delete value;
            }

            inline void operator = (const KeyValuePair<A,B>& pair)
            {
                *key = *pair.key;
                *value = *pair.value;
            }

            inline bool operator == (const KeyValuePair<A,B>& pair) const
            {
                return *key == *(pair.key) && *value == *(pair.value);
            }
            inline bool operator == (std::nullptr_t aNullptr) const
            {
                return *key == aNullptr && *value == aNullptr;
            }
            inline bool operator != (const KeyValuePair<A,B>& pair) const
            {
                return *key != *(pair.key) && *value != *(pair.value);
            }
            inline bool operator != (std::nullptr_t aNullptr) const
            {
                return *key != aNullptr && *value != aNullptr;
            }

            inline KeyValuePair<A,B> operator ++ () noexcept
            {
                key ++;
                value ++;
                return *this;
            }

            inline KeyValuePair<A,B> MakePair(const A& _key,const B& _value)
            {
                return KeyValuePair(_key, _value);
            }
        };

        template <typename A , typename B>
        class Dictionary : vector<KeyValuePair<A,B>>
        {
        public:
            Dictionary() = default;
            Dictionary(const Dictionary<A,B>&) = default;

            typename vector<KeyValuePair<A,B>>::iterator FindIterator(const A& key) const
            {
                typename vector<KeyValuePair<A, B>>::iterator it;
                for (it = this->begin(); it != this->end(); ++it)
                {
                    if (*(it->key) == key)
                    {
                        return it;
                    }
                }
                return it;
            }

            B * FindValue(const A& key) const
            {
                if(std::is_arithmetic<A>())
                {
                    if(this->at(key) != nullptr)
                    {
                        KeyValuePair<A,B> tempPair = this->at(key);
                        return tempPair.value;
                    }
                    else
                    {
                        return nullptr;
                    }
                }
                else
                {
                    typename vector<KeyValuePair<A,B>>::iterator it;
                    for(it = this->begin(); it != this->end(); ++it)
                    {
                        if(*(it->key) == key)
                        {
                            return it->value;
                        }
                    }
                    return nullptr;
                }
            }

            inline void Add(const KeyValuePair<A,B>& pair)
            {
                this->push_back(pair);
            }

            inline void Remove(const A& key)
            {
                this->erase(FindIterator(key));
            }
        };
}}
#endif //DIVISIONCORE_DICTIONARY_H
