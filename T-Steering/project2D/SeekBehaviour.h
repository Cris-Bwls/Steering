#pragma once
#include "BaseBehaviour.h"
class SeekBehaviour :
	public BaseBehaviour
{
public:
	SeekBehaviour();
	~SeekBehaviour();

	Vector2 Update(Agent* pAgent, float fDeltaTime);
};

