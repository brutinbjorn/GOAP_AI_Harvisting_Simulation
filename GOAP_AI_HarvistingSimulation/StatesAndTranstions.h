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
	void Update(Elite::Blackboard* pBlackboard, float deltaTime)  override
	{
		std::cout << "Entered move state " << std::endl;

		
		GOAPAgent* pAgent = nullptr;
		pBlackboard->GetData("Agent", pAgent);

		bool* isPerforming = nullptr;
		pBlackboard->GetData("IsPerformingAction", isPerforming);
		bool* pIsInRange = nullptr;
		pBlackboard->GetData("IsInRange", pIsInRange);

		if (!pAgent) 
			return;
		
		if(!pAgent->HasAPlan())
			return;

		std::list<Action*> Plan = pAgent->GetCurrentPlan();


		
		GameObject* object = Plan.front()->GetTarget();
		
		if(Plan.front()->RequiresInRange() && object != nullptr)
		{
			if(!Plan.front()->IsInRange())
			{
				bool GotInRange = pAgent->MoveAgent(Plan.front(), deltaTime);


				(*pIsInRange) = GotInRange;
			}
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
		std::cout << "Entered idle state " << std::endl;
		GOAPAgent* pAgent = nullptr;
		pBlackboard->GetData("Agent", pAgent);

		bool* HasAPlan = nullptr;
		pBlackboard->GetData("HasAPlan", HasAPlan);
		
		if (!pAgent || !HasAPlan)
			return;

		auto* planner = pAgent->GetPlanner();

		if (!planner)
			return;
		
		std::list<Action*> actionPlan = planner->plan(pAgent,pAgent->CreateGoalState());

		if (!actionPlan.empty()) // plan found
		{
			pAgent->SetActionPlan(actionPlan);
			pAgent->PlanFound(pAgent->CreateGoalState(), actionPlan);
			*HasAPlan = true;
			 
		}

	}
};

class PerformActionState : public Elite::FSMState
{
public:
	PerformActionState() : FSMState() {};
	void Update(Elite::Blackboard* pBlackboard,float dt) override
	{
		std::cout << "Entered perform state " << std::endl;
		
		GOAPAgent* pAgent = nullptr;
		pBlackboard->GetData("Agent", pAgent);
		bool* isPerforming = nullptr;
		pBlackboard->GetData("IsPerformingAction", isPerforming);
		bool* pIsInRange = nullptr;
		pBlackboard->GetData("IsInRange", pIsInRange);

		
		if (!pAgent || !isPerforming)
			return;

		std::list<Action*>& plan = pAgent->GetCurrentPlan();
		if(plan.empty())
		{
			std::cout << "plan did not fail but no Real plan returned" << std::endl;
			return;
		}
		
		Action* currentAction = plan.front();
		if(currentAction->IsDone())
		{
			std::cout << "action done" << std::endl;
			currentAction->PrintActionType();
			
			plan.pop_front();
		}

		//is plan still valid
		if(pAgent->HasAPlan())
		{
			currentAction = plan.front();
			bool inRange = currentAction->RequiresInRange() ? currentAction->IsInRange() : true;

			if(inRange)
			{
				// interact with the object :)
				bool succes = currentAction->Perform(pAgent,dt);
				(*isPerforming) = succes;
				
			}
			(*pIsInRange) = inRange;
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

		return !pAgent->HasAPlan();
	}
};

class IsInRange : public Elite::FSMTransition
{
	bool ToTransition(Elite::Blackboard* pBlackboard) const override
	{
		GOAPAgent* pAgent = nullptr;
		pBlackboard->GetData("Agent", pAgent);
		
		bool* pIsInRange = nullptr;
		pBlackboard->GetData("IsInRange", pIsInRange);
		
		if (!pAgent || !pIsInRange)
			return false;


		return (*pIsInRange);
	}
};

class IsNotInRange : public Elite::FSMTransition
{
	bool ToTransition(Elite::Blackboard* pBlackboard) const override
	{
		GOAPAgent* pAgent = nullptr;
		pBlackboard->GetData("Agent", pAgent);

		bool* pIsInRange = nullptr;
		pBlackboard->GetData("IsInRange", pIsInRange);

		if (!pAgent || !pIsInRange)
			return false;


		return !(*pIsInRange);
	}
};