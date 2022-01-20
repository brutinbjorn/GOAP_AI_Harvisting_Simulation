#pragma once
#include <list>
#include <map>
#include <string>

#include "GameObject.h"


//------------
//0


//------------
//---STATES---
//------------

#include <iostream>

#include "GOAPAgent.h"

class Action
{
public:
	Action() = default;
	virtual ~Action() = default;

	virtual void Reset()
	{
		m_InRange = false;
	}

	virtual bool IsDone() {return false;};
	virtual bool Perform(GOAPAgent* , float ) { return false;};
	virtual bool RequiresInRange() {return false;};
	virtual void SetInRange(bool InRange = false) { m_InRange = InRange; };
	virtual bool IsInRange(GOAPAgent* ) { return m_InRange; };

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

	std::map<std::string, bool> GetPreconditions() const { return m_Preconditions; };
	
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

	std::map<std::string, bool> GetEffects() const { return m_Effects; };
	
	float GetCost() { return m_Cost; };

	virtual bool CheckProceduralPrecondition(GOAPAgent* pAgent, std::vector<GameObject*>* WorldObjects)= 0;
	
	GameObject* GetTarget() const { return m_pTarget; };

	virtual void PrintActionType() { std::cout << "empty action, "; };
	

protected:
	std::map<std::string, bool> m_Preconditions{};
	std::map<std::string, bool> m_Effects{};
	float m_Cost = 1.f;
	bool m_InRange = false;
	GameObject* m_pTarget = nullptr;
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

