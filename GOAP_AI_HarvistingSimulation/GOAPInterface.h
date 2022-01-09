#pragma once
#include <map>
#include <string>
#include <vector>

#include "Actions.h"

class GOAPInterface
{
public:
	GOAPInterface() = default;
	virtual ~GOAPInterface() = default;
	virtual std::map<std::string,bool> GetWorldState() = 0;
	virtual std::map<std::string,bool> CreateGoalState() = 0;

	virtual void PlanFailed(std::map<std::string,bool> failedGoal) = 0;
	virtual void PlanFound(std::map<std::string, bool> goal, std::vector<Action*> actions) = 0;

	virtual void ActionsFinished() = 0;
	virtual void PlanAborted(Action* aborter) = 0;
	virtual bool MoveAgent(Action* nextAction) = 0;
};
