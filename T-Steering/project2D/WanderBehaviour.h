#pragma once
#include "BaseBehaviour.h"
class WanderBehaviour :
	public BaseBehaviour
{
public:
	WanderBehaviour(float fRadius, float fDistance, float fJitter);
	~WanderBehaviour();

	Vector2 Update(Agent* pAgent, float fDeltaTime);

private:
	// Functions
	Vector2 WanderSeek(Agent* pAgent, float fDeltaTime, Vector2 v2Pos);
	Vector2 WanderTarget(Agent* pAgent);
	
	float m_fRadius;
	float m_fDistance;
	float m_fJitter;


};

