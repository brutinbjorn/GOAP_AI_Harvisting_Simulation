#pragma once
#include <iostream>

#include "GameObject.h"
#include "GOAPAgent.h"

class BaseSpot : public GameObject
{
public:
	BaseSpot(const Elite::Vector2& pos, float Radius) :
	GameObject(pos), m_Radius(Radius) {};

	virtual void DropOffResources(GOAPAgent* pAgent);

	virtual void PickUpTool(GOAPAgent* pAgent);

private:
	float m_Radius = 1.f;
	int m_CollectedScore = 0;
};

