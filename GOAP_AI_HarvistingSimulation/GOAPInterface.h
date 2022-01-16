#pragma once
#include <list>
#include <map>
#include <string>
#include <vector>

#include "GameObject.h"


class Action;

class GOAPInterface : public GameObject
{
public:
	GOAPInterface() = default;
	virtual ~GOAPInterface() =default;
	virtual std::map<std::string,bool> GetWorldState() = 0;
	virtual std::map<std::string,bool> CreateGoalState() = 0;

	virtual void PlanFailed(std::map<std::string,bool> failedGoal) = 0;
	virtual void PlanFound(std::map<std::string, bool> goal, std::list<Action*> actions) = 0;

	virtual void ActionsFinished() = 0;
	virtual void PlanAborted(Action* aborter) = 0;
	//virtual bool MoveAgent(Action* nextAction) = 0;
};

