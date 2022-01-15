#pragma once
#include <iostream>


#include "Actions.h"
#include "EFiniteStateMachine.h"
#include "GOAPAgent.h"
#include "EliteMath/EVector2.h"

class MoveState : public Elite::FSMState
{
public:
	MoveState() : FSMState() {};
	virtual void OnEnter(Elite::Blackboard* pBlackboard) override
	{
		GOAPAgent* pAgent = nullptr;
		pBlackboard->GetData("Agent", pAgent);

		Elite::Vector2* target = nullptr;
		pBlackboard->GetData("MoveToTarget", target);

		if (!pAgent || !target) 
			return;

		std::vector<Action*> plan = pAgent->GetCurrentPlan();

		GameObject* object = plan[0]->GetTarget();
		if(plan[0]->RequiresInRange() && object != nullptr)
		{
			(*target) = object->GetPosition();
			
		}
		
		
	}
};

class IdleState : public  Elite::FSMState
{
public:
	IdleState() : FSMState() {};
	//void OnEnter(Elite::Blackboard* pBlackboard) override
	//{
	//}
	void Update(Elite::Blackboard* pBlackboard, float deltaTime) override
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
		if (!pAgent)
			return;

		std::vector<Action*> plan = pAgent->GetCurrentPlan();
		Action* currentAction = plan.front();
		if(currentAction->IsDone())
		{
			//std::vector<Action*>
		}
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

class HasNoPlan : public Elite::FSMTransition
{
	bool ToTransition(Elite::Blackboard* pBlackboard) const override
	{
		GOAPAgent* pAgent = nullptr;
		pBlackboard->GetData("Agent", pAgent);
		if (!pAgent)
			return false;

		return pAgent->HasAPlan();
	}
};
