#pragma once
#include "EGraphNodeTypes.h"
#include "GOAPAgent.h"
#include "Resources.h"

class LocationNode : public Elite::GraphNode
{
public:
	LocationNode(int idx):GraphNode(idx){}
};


class AgentBase : public LocationNode
{
public:
	AgentBase(int idx) :LocationNode(idx){}

	void DropOffResource(){};
private:
	
};

class ResourceNode : public LocationNode
{
public:
	ResourceNode(int idx): LocationNode(idx){}

	bool GatherResource(GOAPAgent* m_Agent,Resource& NewResource){};
};
