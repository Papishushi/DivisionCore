#pragma once

#include "Component.h"
#include "Transform.h"

#include <list>
#include <iterator>

using namespace std;

class GameObject : private Object<GameObject>
{
private:
    list<Component> attachedComponents;
protected:
	static list<GameObject> instancedGameObjects;
public:
	GameObject();
	GameObject(string name);
	GameObject(string name, Transform transform);
	GameObject(string name, Transform transform, list<Component> components);
	~GameObject();

	bool activeInHierarchy;
	bool activeSelf();
	bool isStatic;
	uint_least8_t layer;
	uint_least8_t scene;
	unsigned long sceneCullingMask;
	string tag;
	Transform transform;

	void SetActive(const bool isActive);
	void AddComponent(const typename Component type);

	inline bool CompareTag(const string tag);

	void SendMessageLocal(const void* method);
	void SendMessageChildren(const void* method);
	void SendMessageParent(const void* method);

	bool TryGetComponent(const typename Component type);

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

	static GameObject CreatePrimitive();
	static GameObject Find(const string name);
	static GameObject * FindGameObjectsWithTag(const string name);
	static GameObject FindWithTag(const string name);
};