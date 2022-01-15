#include "GOAP_Application.h"

#include "MineCoalAction.h"
#include "DropOffCoalAction.h"
GOAP_Application::~GOAP_Application()
{
	delete m_pAgent;

	delete m_pPlanner;
	
	for (int i = 0; i < m_WorldObjects.size(); i++)
		delete m_WorldObjects[i];

	for (int i = 0; i < m_pStates.size(); i++)
		delete m_pStates[i];

	for (int i = 0; i < m_pTransitions.size(); i++)
		delete m_pTransitions[i];
	
	
	
}

void GOAP_Application::Start()
{
	//locations
	ResourceSpot* recourceSpot1 = new ResourceSpot({ 50,100 }, 3);
	m_WorldObjects.push_back(recourceSpot1);

	//agent
	m_pAgent = new GOAPAgent({0, 0});
	m_pPlanner = new Planner(&m_WorldObjects);

	Elite::Blackboard* newBB = CreateBlackboard(m_pAgent);

	//states
	auto* idle = new IdleState();
	m_pStates.push_back(idle);
	auto* seek = new MoveState();
	m_pStates.push_back(seek);
	auto* performAction = new PerformActionState();
	m_pStates.push_back(performAction);

	//Transitions
	auto* haveAplan = new HasAPlan();
	m_pTransitions.push_back(haveAplan);
	auto* hasNoPlan = new HasNoPlan();
	m_pTransitions.push_back(hasNoPlan);


	//Actions
	auto* CollectOreAction = new MineCoalAction();
	CollectOreAction->SetresourceSpot(recourceSpot1);
	m_pAgent->AddAction(CollectOreAction);
	auto* DropOffCoalAction = new ::DropOffCoalAction();
	m_pAgent->AddAction(DropOffCoalAction);
	

	
	auto* pFSM = new Elite::FiniteStateMachine(idle, newBB);

	pFSM->AddTransition(idle, performAction, haveAplan);
	pFSM->AddTransition(performAction, idle, hasNoPlan);

	

	m_pAgent->SetPlanner(m_pPlanner);
	m_pAgent->SetDicisionMaking(pFSM);
}

void GOAP_Application::Update(float dt)
{
	m_pAgent->Update(dt);
}

Elite::Blackboard* GOAP_Application::CreateBlackboard(GOAPAgent* a)
{
	Elite::Blackboard* pBlackboard = new Elite::Blackboard();
	pBlackboard->AddData("Agent", a);
	pBlackboard->AddData("MoveToTarget", static_cast<Elite::Vector2*>(nullptr)); // Needs the cast for the type
	pBlackboard->AddData("GameObjects", &m_WorldObjects);
	pBlackboard->AddData("Time", 0.0f);

	return pBlackboard;
}
