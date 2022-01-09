#pragma once
#include "EGraphNodeTypes.h"



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

//class ResourceNode : public LocationNode
//{
//public:
//	ResourceNode(int idx): LocationNode(idx){}
//	bool GatherResource(GOAPAgent* ,ResourceNode& ){return false;};
//};
