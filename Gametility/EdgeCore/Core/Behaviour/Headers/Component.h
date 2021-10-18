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
	Transform transform;

	inline bool CompareTag(const string tag);

	void SendMessageLocal(const void* Method);
	void SendMessageChildren(const void* Method);
	void SendMessageParent(const void* Method);
	
	bool TryGetComponent(Component& component);
	
	template <typename T> T GetComponent();
	template <typename T> T GetComponentInChildren();
	template <typename T> T GetComponentInParent();
	template <typename T> T* GetComponents();
	template <typename T> T* GetComponentsInChildren();
	template <typename T> T* GetComponentsInParent();
};