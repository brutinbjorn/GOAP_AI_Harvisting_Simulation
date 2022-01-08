#pragma once
#include "GOAP_Planner.h"
#include "LocationNode.h"


class GOAPAgent
{
public:
	GOAPAgent(LocationNode* startLocation)
	: m_pLocation(startLocation)
	{
		
	}


	void SetLocation(LocationNode* newLocation) { m_pLocation = newLocation; }
	LocationNode* GetCurrentLocation() const { return m_pLocation; }
	

	void SetDisicionMaking();
	
//	bool MoveToNeighbouringLocation(Node* NewLowLocation)

private:
	GOAP_Planner* m_pPlanner = nullptr;

	LocationNode* m_pLocation = nullptr;
	
};

