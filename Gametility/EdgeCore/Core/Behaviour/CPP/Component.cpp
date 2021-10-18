#include "pch.h"
#include "Component.h"

Component::Component(GameObject parent)
{
	name = This().ToString();
	hideFlags = HideFlags::VISIBLE;

	gameObject = parent;
}
