#pragma once
#include "EFiniteStateMachine.h"
#include "GOAPAgent.h"

#include "Planner.h"
#include "StatesAndTranstions.h"


class GOAP_Application
{
public:
	GOAP_Application() {}
	virtual ~GOAP_Application();

	void Start();

	void Update(float dt);

	Elite::Blackboard* CreateBlackboard(GOAPAgent* a);

private:
	GOAPAgent* m_pAgent = nullptr;
	Planner* m_pPlanner = nullptr;
	
	
	std::vector<GameObject*> m_WorldObjects;
	std::vector<Elite::FSMState*> m_pStates;
	std::vector<Elite::FSMTransition*> m_pTransitions;
};

