#pragma once

#include <algorithm> 
#include <iostream>
#include <cstdint>
#include <string>
#include <list>
#include <iterator>
#include <tuple>
#include "Transform.h"

using namespace std;

enum class HideFlags
{
	HIDDEN = 0,
	VISIBLE = 1
};

typedef uint8_t byte;

template <typename T>
class Object 
{
private:
	const char QUOTE = '"';

	static list<Object> instancedObjects;
	static list<byte> updatedInstancesID;

	uint_least8_t instanceID;
protected:
	/// <summary>
/// Return this object as a reference.
/// </summary>
/// <returns></returns>
	inline T This() const
	{
		return *this;
	}
public :

	HideFlags hideFlags;
	string name;
	
	Object()
	{
		std::list<byte>::iterator it;
		uint_least8_t counter = 0;

		for (it = updatedInstancesID.begin(); it != updatedInstancesID.end(); ++it)
		{
			if (*it == 0)
			{
				updatedInstancesID.push_back(1);
				instancedObjects.push_back(This());

				instanceID = counter;
				name = "Object" + instanceID;

				return;
			}

			counter++;
		}
	}
	~Object()
	{
		updatedInstancesID.remove(instanceID, 0);
		instancedObjects.remove(instanceID, This());
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

	inline string ToString() const
	{
		return name;
	}
	inline string ToJson() const
	{
		return "{" +
			QUOTE + "instanceID" + QUOTE + ": " + QUOTE + instanceID + QUOTE +
			QUOTE + "hideFlags" + QUOTE + ": " + QUOTE + instanceID + QUOTE +
			QUOTE + "name" + QUOTE + ": " + QUOTE + instanceID + QUOTE +
			"}";
	}

	static T* Instantiate(const  T& object, Transform parent, string name)
	{
		T* tempPtr = new T(object);

		return tempPtr;
	}
	static void Destroy(const T* obj)
	{
		delete obj;
	}
	static void Destroy(const T* obj, const bool isArray)
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

	template <typename Type> static void ModifyArray(Type * original, const uint_least8_t size, const uint_least8_t newSize)
	{
		// realloc
		Type* temp = new Type[newSize];

		if (original != nullptr)
		{
			std::copy(original, original + size - 1, temp);
			delete [] original;
		}

		original = temp;
	}

	template <typename Type> static Type FindObjectOfType()
	{
		for (int i = 0; i < instancedObjects->*instancedObjects.size(); i++)
		{
			if (dynamic_cast<Type*>(instancedObjects[i]) != nullptr)
			{
				return instancedObjects[i];
			}
		}
		return nullptr;
	}
	template <typename Type> static Type* FindObjectsOfType()
	{
		Type* tempArr = nullptr;
		uint_least8_t counter = 0;

		for (int i = 0; i < instancedObjects->*instancedObjects.size(); i++)
		{
			if (dynamic_cast<Type*>(instancedObjects[i]) != nullptr)
			{			
				ModifyArray(tempArr, counter, counter + 1);
				
				tempArr[counter] = instancedObjects[i];

				counter++;
			}
		}

		return tempArr;
	}
	
	static T * DontDestroyOnLoad()
	{
		T* instance = new T(This());
		return instance;
	}
};