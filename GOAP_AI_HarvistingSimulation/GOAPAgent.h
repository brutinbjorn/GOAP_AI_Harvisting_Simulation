#pragma once

#include <vector>
#include "EIGraph.h"
#include "GOAPInterface.h"
#include "Inventory.h"
#include "LocationNode.h"
#include "Actions.h"

class GOAPAgent : public GOAPInterface
{
public:

	GOAPAgent(Elite::IGraph<LocationNode, Elite::GraphConnection>* world, LocationNode* start);
	~GOAPAgent() = default;
	std::map<std::string, bool> GetWorldState() override;
	std::map<std::string, bool> CreateGoalState() override;
	void PlanFailed(std::map<std::string, bool> failedGoal) override {};
	void PlanFound(std::map<std::string, bool> goal, std::vector<Action*> actions) override;
	void ActionsFinished() override;
	void PlanAborted(Action* aborter) override;
	bool MoveAgent(Action* nextAction) override;

private:
	Inventory m_inventory;
	LocationNode* m_pLocation = nullptr;
	Elite::IGraph<LocationNode, Elite::GraphConnection>* m_pWorldNodes;

};

