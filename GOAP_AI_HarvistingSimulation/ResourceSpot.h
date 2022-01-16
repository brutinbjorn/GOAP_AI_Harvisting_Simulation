#pragma once
#include "GameObject.h"

class ResourceSpot : public GameObject
{
public:
	ResourceSpot(const Elite::Vector2& pos, float Radius)
		: GameObject(pos), m_Radius(Radius)
	{}

private:
	float m_Radius = 1.f;
};

