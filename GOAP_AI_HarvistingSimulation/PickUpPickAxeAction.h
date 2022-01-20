#pragma once
#include "Actions.h"
#include "BaseSpot.h"

class PickUpPickAxeAction :
    public Action
{
public:
	PickUpPickAxeAction()
	{
		//AddPrecondition("HasTool", true);
		AddPrecondition("HasPickAxe", false);
		AddEffect("HasPickAxe", true);
	}

	void Reset() override
	{
		m_PickedUp = false;
		m_pBaseSpot = nullptr;
		
		//if (m_pTarget)
		//	delete m_pTarget;
	};

	bool IsDone() override { return m_PickedUp; };

	bool RequiresInRange() override { return true; };

	bool IsInRange(GOAPAgent* pAgent) override
	{
		return (Elite::Distance(m_pBaseSpot->GetPosition(), pAgent->GetPosition()) < 1.f);
	}

	
	bool CheckProceduralPrecondition(GOAPAgent* pAgent, std::vector<GameObject*>* world) override
	{
		BaseSpot* closest = nullptr;
		float ClosestDistance = 0.f;
		for (GameObject* ob : *world)
		{
			BaseSpot* rSpot = dynamic_cast<BaseSpot*>(ob);
			if (rSpot)
			{
				if (closest == nullptr)
				{
					closest = rSpot;
					ClosestDistance = Elite::Distance(pAgent->GetPosition(), rSpot->GetPosition());
				}
				else
				{
					float Distance = Elite::Distance(pAgent->GetPosition(), rSpot->GetPosition());
					if (Distance < ClosestDistance)
					{
						closest = rSpot;
						ClosestDistance = Distance;
					}
				}
			}
		}

		m_pBaseSpot = closest;
		m_pTarget = closest;

		return m_pBaseSpot != nullptr;

	};

	bool Perform(GOAPAgent* pAgent, float dt) override
	{
		if (pAgent->GetRefInventory().ToolType != "ToolPickAxe")
		{
			pAgent->GetRefInventory().ToolType = "ToolPickAxe";
			pAgent->GetRefInventory().m_ToolHealth = 3;
			std::cout << "picked up tool " << std::endl;

			m_PickedUp = true;
			return true;
		}
		return false;
	}

	void PrintActionType() override { std::cout << "PickedUpToolAction, "; };


	void SetBaseSpot(BaseSpot* pResource) { m_pBaseSpot = pResource; };
private:
	bool m_PickedUp = false;
	BaseSpot* m_pBaseSpot = nullptr;
};

