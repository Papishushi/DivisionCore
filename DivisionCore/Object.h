#pragma once

#include <algorithm> 
#include <iostream>
#include <cstdint>
#include <string>
#include <list>
#include <iterator>
#include <tuple>
#include <map>

using namespace std;
namespace DivisionCore
{
	enum class HideFlags
	{
		HIDDEN = 0,
		VISIBLE = 1
	};

	typedef uint8_t byte;
    typedef uint_least8_t dynamic_byte;

	template <typename T> class Object
	{
        typedef map<dynamic_byte ,Object> ObjectDictionary;

        typedef map<HideFlags , string> HideFlagsLookupTable;
	private:
        static ObjectDictionary idInstanceDictionary;

        static HideFlagsLookupTable hideFlagsLookupTable;

        dynamic_byte instanceID;
    public:
		HideFlags hideFlags;
		string name;

		Object()
		{
            if(hideFlagsLookupTable.empty())
            {
                hideFlagsLookupTable.insert(pair<HideFlags, string>(HideFlags::VISIBLE, "Visible"));
            }
            if(idInstanceDictionary.empty())
            {
                instanceID = 0;

                name = "Object" + instanceID;
                hideFlags = HideFlags::VISIBLE;

                idInstanceDictionary.insert(pair<dynamic_byte ,Object>(instanceID, *this));
            }
            else
            {
                dynamic_byte counter = 0;

                typename ObjectDictionary::iterator it;
                for (it = idInstanceDictionary.begin(); it != idInstanceDictionary.end(); ++it)
                {
                    if(&(it->first) == nullptr)
                    {
                        instanceID = counter;

                        name = "Object" + instanceID;
                        hideFlags = HideFlags::VISIBLE;

                        idInstanceDictionary.insert(pair<dynamic_byte ,Object>(instanceID, *this));
                    }
                    counter++;
                }
            }
		}
		~Object()
		{
            std::remove(idInstanceDictionary.begin(), idInstanceDictionary.end(), instanceID);
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
			return std::tie(instanceID, hideFlags, name) == std::tie(other.instanceID, other.hideFlags, other.name);
		}
		inline bool operator != (const Object& other) const
		{
			return tie(instanceID, hideFlags, name) != std::tie(other.instanceID, other.hideFlags, other.name);
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
			return R"({"instanceID": ")" + to_string(instanceID) + "\"" +
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
		static void Destroy(const T* obj)
		{
            if(obj != nullptr)
            {
                delete obj;
            }
		}
		static void Destroy(const T* obj, const bool isArray)
		{
            if(obj != nullptr)
            {
                if (isArray)
                {
                    delete[] obj;
                }
                else
                {
                    delete obj;
                }
            }
		}

		template <typename Type> static Type FindObjectOfType()
		{
            typename ObjectDictionary::iterator it;
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

            typename ObjectDictionary::iterator it;
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
