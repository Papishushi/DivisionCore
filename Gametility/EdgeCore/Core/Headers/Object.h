#pragma once

#include <iostream>
#include <cstdint>
#include <string>
#include <list>
#include <iterator>

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
protected:
	static list<Object> instancedObjects;
	static list<byte> updatedInstancesID;
private:
	uint_least8_t instanceID;
public :

	HideFlags hideFlags;
	string name;
	
	Object()
	{
		list<byte>::iterator it;
		uint_least8_t counter = 0;

		for (it = updatedInstancesID.begin(); it != updatedInstancesID.end(); ++it)
		{
			counter++;
			if (*it == 0)
			{
				updatedInstancesID.assign(counter, 1);
				instancedObjects.assign(counter, This());

				instanceID = counter;
				name = "Object" + instanceID;

				return;
			}
		}
	}
	~Object()
	{
		updatedInstancesID.assign(instanceID, 0);
		instancedObjects.assign(instanceID, This());
	}

	inline bool operator - () const
	{
		return this;
	}
	inline bool operator ! () const
	{
		return !this;
	}
	inline bool operator == (const Object& other) const
	{
		return *this == other ? true : false;
	}
	inline bool operator != (const Object& other) const
	{
		return *this != other ? true : false;
	}

	/// <summary>
	/// Return this object.
	/// </summary>
	/// <returns></returns>
	inline T This() const
	{
		return *this;
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

	}

	static Object* Instantiate(const  Object* gameObject)
	{
		Object* tempPtr = new(Object);
		tempPtr = gameObject;

		return tempPtr;
	}
	static void Destroy(const Object* obj)
	{
		delete obj;
	}
	static T FindObjectOfType()
	{
		for (int i = 0; i < instancedObjects->*instancedObjects.size(); i++)
		{
			if (dynamic_cast<T*>(instancedObjects[i]) != nullptr)
			{
				return instancedObjects[i];
			}
		}
		return nullptr;
	}
	static T* FindObjectsOfType()
	{
		for (int i = 0; i < instancedObjects->*instancedObjects.size(); i++)
		{
			if (dynamic_cast<T*>(instancedObjects[i]) != nullptr)
			{
				return instancedObjects[i];
			}
		}
		return nullptr;
	}
	static void DontDestroyOnLoad()
	{
		return;
	}
};