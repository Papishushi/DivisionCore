#pragma once

#include "Vectors.h"
#include "Component.h"

class Transform : Component
{
public:
	Gametility::Vectors::Vector2 position;
	Gametility::Vectors::Vector3Euler rotation;
	Gametility::Vectors::Vector2 scale;
};