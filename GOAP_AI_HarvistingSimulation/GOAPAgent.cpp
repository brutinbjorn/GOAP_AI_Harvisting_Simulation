#include <iostream>

#include "GOAPAgent.h"

#include "Actions.h"
#include "EBFS.h"
#include "EHeuristicFunctions.h"
#include "Planner.h"


//=== Management ===
//#define SAFE_DELETE(p) if (p) { delete (p); (p) = nullptr; }

//GOAPAgent::GOAPAgent( Elite::IGraph<LocationNode, Elite::GraphConnection>* world, LocationNode* start):
//
//	m_pWorldNodes(world)
//{
//	m_pLocation = start;
//	
//}

GOAPAgent::GOAPAgent(Elite::Vector2 startPos)	
{
	SetPosition(startPos);
}

GOAPAgent::~GOAPAgent()
{
	//SAFE_DELETE(m_pPlanner);
	if (m_pPlanner)
		delete m_pPlanner;
	m_pPlanner = nullptr;
	
	SAFE_DELETE(m_pDesicionMaking);
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
	for (auto action : actions)
	{
		action->PrintActionType();
	}
}

void GOAPAgent::ActionsFinished()
{
	std::cout << "GOAP Plan Finished" << std::endl;
}

void GOAPAgent::SetPlanner(Planner* newPlanner)
{
	if (m_pPlanner)
		delete m_pPlanner;
	m_pPlanner = nullptr;

	m_pPlanner = newPlanner;
	
}

bool GOAPAgent::MoveAgent(Action* nextAction,float dt)
{
	auto val = nextAction->GetTarget();

	Elite::Vector2 target = val->GetPosition();

	Elite::Vector2 towards = target - m_pos;
	m_pos += Elite::GetNormalized(towards) * m_MoveSpeed * dt;
	if(Elite::Distance(target,m_pos) < 1.f)
	{
		nextAction->SetInRange(true);
		return true;
	}
	return false;
}

void GOAPAgent::PlanAborted(Action*  aborter)
{
	std::cout << "GOAP plan aborted" << std::endl;
}



//bool GOAPAgent::MoveAgent(Action* nextAction)
//{
//	auto target = nextAction->GetTarget();
//
//	auto m_pHeuristicFunction = Elite::HeuristicFunctions::Chebyshev;
//
//	auto pathFinder = Elite::BFS<LocationNode,Elite::GraphConnection>(m_pWorldNodes);
//
//	auto path =pathFinder.FindPath(m_pLocation, target);
//
//	if (path.back() == m_pLocation)
//		return true;
//
//	if (path.size() > 1)
//		m_pLocation = path[1];
//	std::cout << "agent moved loc" << std::endl;
//	if (m_pLocation == target)
//	{
//		
//		return true;
//	}
//	return false;
//	
//}
//
