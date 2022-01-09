#pragma once

#include "EIGraph.h"
#include "LocationNode.h"
#include "Planner.h"
#include "GOAPAgent.h"

class GOAP_Application
{
public:
	GOAP_Application() {};
	virtual ~GOAP_Application()
	{
		//if(m_pPlanner)
		delete m_pPlanner;
	};

	void Start()
	{
		m_pPlanner = new Planner();
		m_pGraph = new Elite::IGraph<LocationNode, Elite::GraphConnection>(false);

		auto BaseNode = new AgentBase(m_pGraph->GetNextFreeNodeIndex());
		
		m_pGraph->AddNode(BaseNode);


		m_pAgent = new GOAPAgent(m_pGraph,BaseNode); // "spawn agent at the base"//.


		
	};
	void Update(float ) {};

private:
	GOAPAgent* m_pAgent = nullptr;
	Elite::IGraph<LocationNode, Elite::GraphConnection>* m_pGraph = nullptr;
	Planner* m_pPlanner = nullptr;
	
};

