#pragma once
#include "GOAPAgent.h"
#include "EIGraph.h"
#include "LocationNode.h"

class GOAP_Application
{
public:
	GOAP_Application() {};
	virtual ~GOAP_Application(){};

	void Start()
	{

		m_pGraph = new Elite::IGraph<LocationNode, Elite::GraphConnection>(false);

		auto BaseNode = new AgentBase(m_pGraph->GetNextFreeNodeIndex());
		m_pGraph->AddNode(BaseNode);






		m_pAgent = new GOAPAgent(BaseNode); // "spawn agent at the base"//.


		
	};
	void Update(float ) {};

private:
	GOAPAgent* m_pAgent = nullptr;
	Elite::IGraph<LocationNode, Elite::GraphConnection>* m_pGraph = nullptr;
	
	
};

