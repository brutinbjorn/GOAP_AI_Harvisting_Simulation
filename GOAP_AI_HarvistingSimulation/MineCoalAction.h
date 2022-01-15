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
		AddEffect("HasOre", true);
	}

	void Reset() override
	{
		m_mined = false;
		m_ElapsedMineTime = 0.f;
		if (m_pTarget)
			delete m_pTarget;
	};

	bool IsDone() override { return m_mined; };

	bool RequiresInRange() override { return true; };

	bool CheckProceduralPrecondition(GOAPAgent* pAgent,std::vector<GameObject*>* world) override
	{
		ResourceSpot* closest = nullptr;
		float ClosestDistance = 0.f;
		for (GameObject* ob :*world)
		{
			ResourceSpot* rSpot = static_cast<ResourceSpot*>(ob);
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

		if(m_ElapsedMineTime > m_MineDuration)
		{
			pAgent->GetRefInventory().m_Resources.emplace_back(ResourceType::coal) ;
			m_mined = true;
			
		}
		return true;
	}

	void PrintActionType() override { std::cout << "mineCoalAction, "; };


	void SetresourceSpot(ResourceSpot* pResource) { m_pResourceSpot = pResource; };
private:
	bool m_mined = false;
	ResourceSpot* m_pResourceSpot = nullptr;


	float m_MineDuration = 2.f;
	float m_ElapsedMineTime = 0.f;
	
};
