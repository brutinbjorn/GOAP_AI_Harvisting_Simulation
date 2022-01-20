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
	
	SAFE_DELETE(m_pDesicionMaking);


	for (size_t i = 0; i < m_pAvailableActions.size(); i++)
	{
		SAFE_DELETE(m_pAvailableActions[i]);
	}
	
}

std::map<std::string, bool> GOAPAgent::GetWorldState()
{
	std::map<std::string, bool> WorldData;
	WorldData["HasOre"]= !m_inventory.m_Resources.empty();
	WorldData["HasPickAxe"] = m_inventory.ToolType == "ToolPickAxe";

	return WorldData;
}

std::map<std::string, bool> GOAPAgent::CreateGoalState()
{
	std::map<std::string, bool> goal;
	goal["CollectOre"] = true;
	return goal;
	
}

void GOAPAgent::PlanFound(std::map<std::string, bool> goal, std::list<Action*> actions)
{
	std::cout << "GOAP Plan Found" << std::endl;
	for (auto action : actions)
	{
		action->PrintActionType();
	}
	std::cout << std::endl;
}

void GOAPAgent::ActionsFinished()
{
	std::cout << "GOAP Plan Finished" << std::endl;
}

void GOAPAgent::Update(float dt)
{
	m_pDesicionMaking->Update(dt);
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
	
	std::cout << "Goap agent position =:" << m_pos << std::endl;
	
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



