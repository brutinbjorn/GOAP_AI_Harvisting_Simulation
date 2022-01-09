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


class Action
{
public:
	Action() = default;
	virtual ~Action() = default;

	virtual void Reset()
	{
		m_InRange = false;
	}

	virtual bool IsDone() = 0;
	virtual bool Perform() = 0;
	virtual bool RequiresInRange() = 0;
	virtual bool IsInRange() { return m_InRange; };

	void AddPrecondition(std::string key, bool val)
	{
		m_Preconditions[key] = val;
	}

	bool RemovePrecondition(std::string key)
	{
		auto search = m_Preconditions.find(key);
		if (search != m_Preconditions.end())
		{
			m_Preconditions.erase(search);
			return true;
		}
		return false;
	}

	void AddEffect(std::string key, bool val)
	{
		m_Effects[key] = val;
	}
	
	bool RemoveEffect(std::string key)
	{
		auto search = m_Effects.find(key);
		if (search != m_Effects.end())
		{
			m_Effects.erase(search);
			return true;
		}
		return false;
	}

	LocationNode* GetTarget() { return m_pTarget; };

protected:
	std::map<std::string, bool> m_Preconditions{};
	std::map<std::string, bool> m_Effects{};
	float m_Cost = 1.f;
	bool m_InRange = false;
	LocationNode* m_pTarget = nullptr;
};


//class GoToAction : public Action
//{
//public:
//	GoToAction() = default;
//	~GoToAction() = default;
//private:
//	bool m_Arrived = false;
//	LocationNode* m_pTargetLocation = nullptr;
//};
//
//
//class MineOreAction : public Action
//{
//public:
//	MineOreAction(ResourceNode* pResource)
//	{
//		m_Preconditions["HasTool"] = true;
//		m_Preconditions["HasOre"] = false;
//		m_Effects["HasOre"] = true;
//	}
//
//	~MineOreAction() = default;
//
//	void Reset() override
//	{
//		m_Mined = false;
//		m_pResourceNode = nullptr;
//	};
//	bool IsDone() override { return m_Mined; };
//	bool RequiresInRange() override { return true; };
//
//private:
//	bool m_Mined = false;
//	ResourceNode* m_pResourceNode = nullptr;
//};

