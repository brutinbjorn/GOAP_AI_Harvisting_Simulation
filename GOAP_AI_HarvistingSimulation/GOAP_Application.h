#pragma once
#include "GOAPAgent.h"
#include "EIGraph.h"

class GOAP_Application
{
public:
	GOAP_Application() {};
	virtual ~GOAP_Application(){};

	void Start()
	{
		m_pGraph = new Elite::IGraph<Elite::GraphNode, Elite::GraphConnection>(false);
	};
	void Update(float ) {};
private:
	GOAPAgent* m_pAgent = nullptr;
	Elite::IGraph<Elite::GraphNode, Elite::GraphConnection>* m_pGraph = nullptr;
	
	
};

