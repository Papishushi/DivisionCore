#pragma once

#include "Behaviour.h"
#include "GameObject.h"

class RunningBehaviour : Behaviour
{
protected:

public:

	RunningBehaviour();
	~RunningBehaviour();
private:

	void Awake();
	void Start();
	void FixedUpdate();
	void Update();
	void LateUpdate();

};