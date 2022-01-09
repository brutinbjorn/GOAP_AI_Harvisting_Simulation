#include "GOAPAgent.h"

#include <iostream>
//#include "EAStar.h"
#include "EHeuristicFunctions.h"
#include "EBFS.h"

GOAPAgent::GOAPAgent( Elite::IGraph<LocationNode, Elite::GraphConnection>* world, LocationNode* start):

	m_pWorldNodes(world)
{
	m_pLocation = start;
	
}

std::map<std::string, bool> GOAPAgent::GetWorldState()
{
	std::map<std::string, bool> WorldData;
	WorldData["HasOre"]= !m_inventory.m_Resources.empty();

	return WorldData;
}

std::map<std::string, bool> GOAPAgent::CreateGoalState()
{
	std::map<std::string, bool> goal;
	goal["CollectOre"] = true;
	return goal;
	
}

void GOAPAgent::PlanFound(std::map<std::string, bool> goal, std::vector<Action*> actions)
{
	std::cout << "GOAP Plan Found" << std::endl;
}

void GOAPAgent::ActionsFinished()
{
	std::cout << "GOAP Plan Finished" << std::endl;
}

void GOAPAgent::PlanAborted(Action* aborter)
{
	std::cout << "GOAP plan aborted" << std::endl;
}

bool GOAPAgent::MoveAgent(Action* nextAction)
{
	auto target = nextAction->GetTarget();

	auto m_pHeuristicFunction = Elite::HeuristicFunctions::Chebyshev;

	auto pathFinder = Elite::BFS<LocationNode,Elite::GraphConnection>(m_pWorldNodes);

	auto path =pathFinder.FindPath(m_pLocation, target);

	if (path.back() == m_pLocation)
		return true;

	if (path.size() > 1)
		m_pLocation = path[1];
	std::cout << "agent moved loc" << std::endl;
	if (m_pLocation == target)
	{
		
		return true;
	}
	return false;
	
}

