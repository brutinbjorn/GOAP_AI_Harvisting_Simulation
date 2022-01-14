#pragma once
#include "EFiniteStateMachine.h"
#include "GOAPAgent.h"

#include "Planner.h"
#include "StatesAndTranstions.h"


class GOAP_Application
{
public:
	GOAP_Application() {};
	virtual ~GOAP_Application()
	{
		delete m_pPlanner;

		for (int i = 0; i < m_WorldObjects.size(); i++)
			delete m_WorldObjects[i];

	};

	void Start()
	{
		//locations


		
		//agent
		m_pAgent = new GOAPAgent({ 0,0 });
		m_pPlanner = new Planner(&m_WorldObjects);

		Elite::Blackboard* newBB = CreateBlackboard(m_pAgent);

		//states
		auto* idle = new IdleState();
		m_pStates.push_back(idle);
		auto* seek = new SeekState();
		m_pStates.push_back(seek);
		auto* performAction = new PerformActionState();
		m_pStates.push_back(performAction);

		//Transitions
		auto* haveAplan = new HasAPlan();
		m_pTransitions.push_back(haveAplan);

		
		
		
		Elite::FiniteStateMachine* pFSM = new Elite::FiniteStateMachine(idle,newBB);

		

		m_pAgent->SetPlanner(m_pPlanner);
		m_pAgent->SetDicisionMaking(pFSM);
	};
	void Update(float ) {};

	Elite::Blackboard* CreateBlackboard(GOAPAgent* a)
	{
		Elite::Blackboard* pBlackboard = new Elite::Blackboard();
		pBlackboard->AddData("Agent", a);
		pBlackboard->AddData("MoveToTarget", static_cast<Elite::Vector2*>(nullptr)); // Needs the cast for the type
		pBlackboard->AddData("GameObjects", &m_WorldObjects);
		pBlackboard->AddData("Time", 0.0f);

		return pBlackboard;
	}

private:
	GOAPAgent* m_pAgent = nullptr;
	Planner* m_pPlanner = nullptr;
	
	
	std::vector<GameObject*> m_WorldObjects;
	std::vector<Elite::FSMState*> m_pStates{};
	std::vector<Elite::FSMTransition*> m_pTransitions{};
};

