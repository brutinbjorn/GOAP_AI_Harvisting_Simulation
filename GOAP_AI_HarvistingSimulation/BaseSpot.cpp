#include "BaseSpot.h"

void BaseSpot::DropOffResources(GOAPAgent* pAgent)
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

void BaseSpot::PickUpTool(GOAPAgent* pAgent)
{
	auto& inventory = pAgent->GetRefInventory();

	inventory.ToolType = "ToolPickAxe";
	inventory.m_ToolHealth = 3;
}
