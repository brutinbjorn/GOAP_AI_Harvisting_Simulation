#pragma once
#include <iostream>

#include "EFiniteStateMachine.h"
#include "GOAPAgent.h"
#include "EliteMath/EVector2.h"

class SeekState : public Elite::FSMState
{
public:
	SeekState() : FSMState() {};
	virtual void OnEnter(Elite::Blackboard* pBlackboard) override
	{
		GOAPAgent* pAgent = nullptr;
		pBlackboard->GetData("Agent", pAgent);

		Elite::Vector2* target = nullptr;
		pBlackboard->GetData("MoveToTarget", target);

		if (!pAgent) return;
	}
};

class IdleState : public  Elite::FSMState
{
public:
	IdleState() : FSMState() {};
	void OnEnter(Elite::Blackboard* pBlackboard) override
	{
		GOAPAgent* pAgent = nullptr;
		pBlackboard->GetData("Agent", pAgent);

		std::vector<GameObject*>* gameObjects = nullptr;
		pBlackboard->GetData("GameObjects", gameObjects);

		
		if (!pAgent)
			return;

		auto* planner = pAgent->GetPlanner();

		if (!planner)
			return;
		
		std::vector<Action*> actionPlan = planner->plan(pAgent,pAgent->CreateGoalState());

		if (!actionPlan.empty()) // plan found
		{
			pAgent->SetActionPlan(actionPlan);
			pAgent->PlanFound(pAgent->CreateGoalState(), actionPlan);
		}
			
	}
};

class PerformActionState : public Elite::FSMState
{
public:
	PerformActionState() : FSMState() {};
	void OnEnter(Elite::Blackboard* pBlackboard) override
	{
		GOAPAgent* pAgent = nullptr;
		pBlackboard->GetData("Agent", pAgent);
	}
	
};

class HasAPlan : public Elite::FSMTransition
{
	bool ToTransition(Elite::Blackboard* pBlackboard) const override
	{
		GOAPAgent* pAgent = nullptr;
		pBlackboard->GetData("Agent", pAgent);
		if(!pAgent)
			return false;

		return pAgent->HasAPlan();
		
		
	}
};

