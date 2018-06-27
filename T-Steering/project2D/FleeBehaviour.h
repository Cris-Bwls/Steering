#pragma once
#include "BaseBehaviour.h"
class FleeBehaviour :
	public BaseBehaviour
{
public:
	FleeBehaviour();
	~FleeBehaviour();

	Vector2 Update(Agent* pAgent, float fDeltaTime);
};

