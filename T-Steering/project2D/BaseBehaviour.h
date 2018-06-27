#pragma once
#include "Vector2.h"

class Agent;

class BaseBehaviour
{
public:
	BaseBehaviour();
	virtual ~BaseBehaviour();

	virtual Vector2 Update(Agent* pAgent, float fDeltaTime) = 0;
	
	float m_fWeighting;
};

