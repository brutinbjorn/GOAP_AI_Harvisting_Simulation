#pragma once
#include "Actions.h"

#include "EBFS.h"
#include "ResourceSpot.h"

class MineCoalAction :public Action
{
public:
	MineCoalAction()
	{
		//AddPrecondition("HasTool", true);
		AddPrecondition("HasOre", false);
		AddPrecondition("HasPickAxe", true);
		AddEffect("HasOre", true);
	}

	void Reset() override
	{
		m_mined = false;
		m_ElapsedMineTime = 0.f;
		//if (m_pTarget)
		//	delete m_pTarget;
	};

	bool IsDone() override { return m_mined; };

	bool RequiresInRange() override { return true; };

	bool IsInRange(GOAPAgent* pAgent) override
	{
		return (Elite::Distance(m_pResourceSpot->GetPosition(),pAgent->GetPosition()) < 1.f) ;
	}

	bool CheckProceduralPrecondition(GOAPAgent* pAgent,std::vector<GameObject*>* world) override
	{
		ResourceSpot* closest = nullptr;
		float ClosestDistance = 0.f;
		for (GameObject* ob :*world)
		{
			ResourceSpot* rSpot = dynamic_cast<ResourceSpot*>(ob);
			if(rSpot)
			{
				if (closest == nullptr)
				{
					closest = rSpot;
					ClosestDistance = Elite::Distance(pAgent->GetPosition(), rSpot->GetPosition());
				}
				else
				{
					float Distance = Elite::Distance(pAgent->GetPosition(), rSpot->GetPosition());
					if(Distance < ClosestDistance)
					{
						closest = rSpot;
						ClosestDistance = Distance;
					}
				}
			}	
		}

		m_pResourceSpot = closest;
		m_pTarget = closest;

		return m_pResourceSpot != nullptr;
		
	};

	bool Perform(GOAPAgent* pAgent,float dt) override
	{
		m_ElapsedMineTime += dt;

		if(pAgent->GetRefInventory().ToolType == "ToolPickAxe")
		{
			std::cout << "mining..." << std::endl;
			if(m_ElapsedMineTime > m_MineDuration)
			{
				std::cout << "mining done" << std::endl;
				pAgent->GetRefInventory().m_Resources.emplace_back(ResourceType::coal) ;

				pAgent->GetRefInventory().m_ToolHealth--;
				if (pAgent->GetRefInventory().m_ToolHealth <= 0)
					pAgent->GetRefInventory().ToolType = "";
				m_mined = true;
			}
			return true;
		}
		return false;
	}

	void PrintActionType() override { std::cout << "mineCoalAction, "; };


	void SetResourceSpot(ResourceSpot* pResource) { m_pResourceSpot = pResource; };
private:
	bool m_mined = false;
	ResourceSpot* m_pResourceSpot = nullptr;


	float m_MineDuration = 2.f;
	float m_ElapsedMineTime = 0.f;
	
};
