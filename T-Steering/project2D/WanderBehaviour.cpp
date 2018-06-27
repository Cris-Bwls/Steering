#include "WanderBehaviour.h"
#include "Agent.h"
#include <time.h>
#include <random>


WanderBehaviour::WanderBehaviour(float fRadius, float fDistance, float fJitter)
{
	m_fRadius = fRadius;
	m_fDistance = fDistance;
	m_fJitter = fJitter;

	srand(time(0));
}


WanderBehaviour::~WanderBehaviour()
{
}


Vector2 WanderBehaviour::Update(Agent* pAgent, float fDeltaTime)
{
	Vector2 v2Target = WanderTarget(pAgent);
	return WanderSeek(pAgent, fDeltaTime, v2Target);
}

Vector2 WanderBehaviour::WanderSeek(Agent* pAgent, float fDeltaTime, Vector2 v2Pos)
{

	Vector2 v2Dir = v2Pos - pAgent->GetPosition();
	v2Dir.normalise();
	v2Dir *= pAgent->GetMaxSpeed();

	Vector2 v2Accel = v2Dir - pAgent->GetVelocity();

	Vector2 v2Vel = v2Accel * fDeltaTime;

	return v2Vel;
}

Vector2 WanderBehaviour::WanderTarget(Agent* pAgent)
{
	float rot = pAgent->GetRotation();

	float random = rand() * 0.314f;
	Vector2 v2Target;
	v2Target.x = -sinf(random)*m_fRadius;
	v2Target.y = cosf(random)*m_fRadius;

	Vector2 v2Jitter(rand(), rand());
	v2Jitter.normalise();
	v2Jitter *= m_fJitter;

	v2Target += v2Jitter;

	v2Target.normalise();
	v2Target *= m_fRadius;


	Vector2 v2Offset;
	v2Offset.x = -sin(rot)*m_fDistance;
	v2Offset.y = cos(rot)*m_fDistance;

	v2Target += v2Offset + pAgent->GetPosition();

	return v2Target;
}