#pragma once

#include <map>
#include <vector>


#include "EDecisionMaking.h"
#include "GOAPInterface.h"
#include "Inventory.h"


#include "EliteMath/EVector2.h"


class Action;
class Planner;

class GOAPAgent : public GOAPInterface
{
public:

	//GOAPAgent(Elite::IGraph<LocationNode, Elite::GraphConnection> *world, LocationNode* start);

	GOAPAgent(Elite::Vector2 startPos);
	~GOAPAgent() override;
	std::map<std::string, bool> GetWorldState() override;
	std::map<std::string, bool> CreateGoalState() override;

	void AddAction(Action* m_pAction) { m_AvailableActions.push_back(m_pAction); };
	std::vector<Action*> GetAllActions() const { return m_AvailableActions; };

	void SetActionPlan(std::vector<Action*> ActionsToDo) { m_CurrentActions = ActionsToDo; };
	bool HasAPlan() { return !m_CurrentActions.empty(); }
	
	void PlanFailed(std::map<std::string, bool> failedGoal) override {};
	void PlanFound(std::map<std::string, bool> goal, std::vector<Action*> actions) override;
	void PlanAborted(Action* aborter) override;
	
	void ActionsFinished() override;

	void SetDicisionMaking(Elite::FiniteStateMachine* FSM) { m_pDesicionMaking = FSM; };
	void SetPlanner(Planner* newPlanner);
	Planner* GetPlanner() { return m_pPlanner; };
	
	Inventory& GetRefInventory() { return m_inventory; };

	bool MoveAgent(Action* nextAction,float dt);

private:
	//Elite::Vector2 m_pos;
	Inventory m_inventory;

	Elite::IDecisionMaking* m_pDesicionMaking = nullptr;
	
	float m_MoveSpeed = 5.f;
	Planner* m_pPlanner = nullptr;
	
	std::vector<Action*> m_AvailableActions;
	std::vector<Action*> m_CurrentActions;
	
};

