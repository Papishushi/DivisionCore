#pragma once

#include "Behaviour.h"

namespace DivisionCore
{
	class RunningBehaviour : Behaviour
	{
	public:
		RunningBehaviour() = default;

    protected:

		void Awake();
		void Start();
		void FixedUpdate();
		void Update();
		void LateUpdate();
	};
}