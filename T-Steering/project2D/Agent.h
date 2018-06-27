#pragma once
#include "GameObject.h"
#include "Vector2.h"
#include "Texture.h"
#include <vector>

class BaseBehaviour;

class Agent :
	public GameObject
{
public:
	Agent(aie::Texture* pTexture, Vector2 v2Pos, float fRotRadians = 0.0f);
	virtual ~Agent();

	virtual void Update(float fDeltaTime);
	virtual void Draw(aie::Renderer2D* pRenderer);

	void SetVelocity(Vector2 v2Velocity);
	Vector2 GetVelocity();

	void SetMaxSpeed(float fMaxSpeed);
	float GetMaxSpeed();

	void AddBehaviour(BaseBehaviour* pBehaviour, float fWeighting);

protected:
	aie::Texture* m_pTexture;
	
	Vector2 m_v2Velocity;
	float m_fMaxSpeed;

	std::vector<BaseBehaviour*> m_BehaviourList;

	float zoom = 1.0f;
};

