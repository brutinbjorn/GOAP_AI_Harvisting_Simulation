#pragma once
#include <iostream>

#include "GameObject.h"
#include "GOAPAgent.h"

class BaseSpot : public GameObject
{
public:
	BaseSpot(const Elite::Vector2& pos, float Radius) :
	GameObject(pos), m_Radius(Radius) {};

	virtual void DropOffResources(GOAPAgent* pAgent)
	{
		auto& resources = pAgent->GetRefInventory().m_Resources;

		int pointsGained = 0;

		
		for (size_t i = 0; i < resources.size(); i++)
		{
			//resources[i];
			pointsGained++;
		}
		resources.clear();
		std::cout << "points gained for dropped off: " << pointsGained << std::endl;

		m_CollectedScore += pointsGained;

		std::cout << "Total score now: " << m_CollectedScore << std::endl;
		
	}

	virtual void PickUpTool(GOAPAgent* pAgent)
	{
		auto& inventory = pAgent->GetRefInventory();

		inventory.ToolType = "ToolPickAxe";
		inventory.m_ToolHealth = 3;
	}

private:
	float m_Radius = 1.f;
	int m_CollectedScore = 0;
};

