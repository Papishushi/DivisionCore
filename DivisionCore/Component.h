#pragma once

#include <string>

#include "Object.h"
#include "GameObject.h"

using namespace std;

class Component : public Object<Component>
{
public:
	Component(GameObject parent);
	~Component();

	GameObject gameObject;
	string tag;
	inline Transform transform()
	{
		return gameObject.transform;
	}

	inline bool CompareTag(const string _tag)
	{
		gameObject.CompareTag(_tag);
	}

	void SendMessageLocal(const void* Method);
	void SendMessageChildren(const void* Method);
	void SendMessageParent(const void* Method);

	template <typename T> bool TryGetComponent(T& outComponent) 
	{
		return gameObject.TryGetComponent(outComponent);
	}
	
	template <typename T> T GetComponent()
	{
		return gameObject.GetComponent<T>();
	}
	template <typename T> T GetComponentInChildren()
	{
		return gameObject.GetComponentInChildren<T>();
	}
	template <typename T> T GetComponentInParent()
	{
		return gameObject.GetComponentInParent<T>();
	}
	template <typename T> T* GetComponents()
	{
		return gameObject.GetComponents<T>();
	}
	template <typename T> T* GetComponentsInChildren()
	{
		return gameObject.GetComponentsInChildren<T>();
	}
	template <typename T> T* GetComponentsInParent()
	{
		return gameObject.GetComponentsInParent<T>();
	}
};