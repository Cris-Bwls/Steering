#include "FleeBehaviour.h"
#include "Input.h"
#include "Vector2.h"
#include "Agent.h"


FleeBehaviour::FleeBehaviour()
{
}


FleeBehaviour::~FleeBehaviour()
{
}

Vector2 FleeBehaviour::Update(Agent* pAgent, float fDeltaTime)
{
	auto input = aie::Input::getInstance();

	Vector2 v2Dest;
	v2Dest.x = 300.0f;
	v2Dest.y = 300.0f;

	Vector2 v2Dir = pAgent->GetPosition() -  v2Dest;
	v2Dir.normalise();
	v2Dir *= pAgent->GetMaxSpeed();

	Vector2 v2Accel = v2Dir - pAgent->GetVelocity();

	Vector2 v2Vel = v2Accel * fDeltaTime;

	return v2Vel;
}