#include "GOAP_Application.h"

#include "MineCoalAction.h"
#include "DropOffCoalAction.h"
#include "PickUpPickAxeAction.h"

GOAP_Application::~GOAP_Application()
{
	delete m_pAgent;

	delete m_pPlanner;
	
	for (size_t i = 0; i < m_WorldObjects.size(); i++)
		delete m_WorldObjects[i];

	for (size_t i = 0; i < m_pStates.size(); i++)
		delete m_pStates[i];

	for (size_t i = 0; i < m_pTransitions.size(); i++)
		delete m_pTransitions[i];
}

void GOAP_Application::Start()
{
	//locations
	ResourceSpot* pRecourceSpot1 = new ResourceSpot({ 40,20 }, 3);
	m_WorldObjects.push_back(pRecourceSpot1);

	auto *pBaseSpot = new BaseSpot({0,0},3);
	m_WorldObjects.push_back(pBaseSpot);
	
	//agent
	m_pAgent = new GOAPAgent({0, 0});
	m_pPlanner = new Planner(&m_WorldObjects);
	Elite::Blackboard* newBB = CreateBlackboard(m_pAgent);

	//states
	auto* idle = new IdleState();
	m_pStates.push_back(idle);
	
	auto* MoveAction = new MoveState();
	m_pStates.push_back(MoveAction);
	
	auto* performAction = new PerformActionState();
	m_pStates.push_back(performAction);

	//Transitions
	auto* pHasAplan = new HasAPlan();
	m_pTransitions.push_back(pHasAplan);
	
	auto* pHasNoPlan = new HasNoPlan();
	m_pTransitions.push_back(pHasNoPlan);

	auto* pIsInRange = new  IsInRange();
	m_pTransitions.push_back(pIsInRange);

	auto* pNotInRange = new  IsNotInRange();
	m_pTransitions.push_back(pNotInRange);

	

	auto* CollectOreAction = new MineCoalAction();
	m_pAgent->AddAction(CollectOreAction);
	
	auto* dropOffCoalAction = new DropOffCoalAction();
	m_pAgent->AddAction(dropOffCoalAction);

	auto* pickupPickaxe = new PickUpPickAxeAction();
	m_pAgent->AddAction(pickupPickaxe);
	
	
	auto* pFSM = new Elite::FiniteStateMachine(idle, newBB);

	pFSM->AddTransition(idle, performAction, pHasAplan);
	pFSM->AddTransition(performAction, idle, pHasNoPlan);


	pFSM->AddTransition(MoveAction, idle, pHasNoPlan);
	pFSM->AddTransition(MoveAction, performAction, pIsInRange);

	pFSM->AddTransition(performAction, MoveAction, pNotInRange);
	

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
	pBlackboard->AddData("IsPerformingAction", &m_AgentDoingAction);
	pBlackboard->AddData("IsInRange", &m_AgentInRange);
	pBlackboard->AddData("HasAPlan", &m_AgentHasAPlan);
	return pBlackboard;
}
