#pragma once


#include "Component.h"
#include "Transform.h"

#include <list>
#include <iterator>

using namespace std;

enum class PrimitiveType
{
	SQUARE = 0,
	CIRCLE = 1,
	TRIANGLE = 2,
	HEXAGON = 3
};

class GameObject : private Object<GameObject>
{
private:
	static list<GameObject> instancedGameObjects;
	bool isActive;
    list<Component> attachedComponents;
public:
	GameObject();
	GameObject(const string name);
	GameObject(const string name, const Transform transform);
	GameObject(const string name, const Transform transform, const list<Component> components);
	GameObject(const GameObject& gameObject);
	~GameObject();

	bool activeInHierarchy;
	inline bool activeSelf()
	{
		return isActive;
	}
	bool isStatic;
	uint_least8_t layer;
	uint_least8_t scene;
	unsigned long sceneCullingMask;
	string tag;
	Transform transform;

	inline void SetActive(const bool _isActive)
	{
		isActive = _isActive;
	}
	template <typename T> inline T AddComponent()
	{
		T * temp = new T();
		attachedComponents.push_back(temp);
		return temp;
	}

	inline bool CompareTag(const string _tag)
	{
		return tag == _tag;
	}

	void SendMessageLocal(const void* method);
	void SendMessageChildren(const void* method);
	void SendMessageParent(const void* method);

	template <typename T> bool TryGetComponent(T& outComponent);

	template <typename T> T GetComponent()
	{
		list<Component>::iterator it;

		for (it = attachedComponents.begin(); it != attachedComponents.end(); ++it)
		{
			if (it == T)
			{
				return it;
			}
		}
		return nullptr;
	}
	template <typename T> T GetComponentInChildren();
	template <typename T> T GetComponentInParent();
	template <typename T> T* GetComponents();
	template <typename T> T* GetComponentsInChildren();
	template <typename T> T* GetComponentsInParent();

	static GameObject CreatePrimitive(PrimitiveType primitiveType);
	static GameObject Find(const string name);
	static GameObject * FindGameObjectsWithTag(const string tag);
	static GameObject FindWithTag(const string tag);
};