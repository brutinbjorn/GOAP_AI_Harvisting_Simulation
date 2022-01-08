#pragma once
#include <list>
#include <map>
#include <string>

#include "LocationNode.h"

//------------
//0


//------------
//---STATES---
//------------


class GOAPAction
{
public:
	GOAPAction(){};

	virtual void Reset()
	{
		m_InRange = false;
	}
	virtual bool IsDone() = 0;
	
protected:
	std::map<std::string, bool> m_Preconditions{};
	std::map<std::string, bool> m_Effects{};
	float m_Cost = 1.f;
	bool m_InRange = false;
	
};

class MineOreAction : public  GOAPAction
{
public:
	MineOreAction(ResourceNode* pResource)
	{
		m_Preconditions["HasTool"] = true;
		m_Preconditions["HasOre"] = true;
 	}
	
private:
	bool m_Mined = false;
	ResourceNode* m_pResourceNode = nullptr;
};

