#pragma once
#include "Actions.h"
#include "BaseSpot.h"


class DropOffCoalAction :
    public Action
{
public:
	DropOffCoalAction() {
		AddPrecondition("HasOre", true); // can't drop off ore if we don't already have some
		AddEffect("HasOre", false); // we now have no ore
		AddEffect("CollectOre", true); // we collected ore
	}


	
	void Reset() override
	{
		m_DroppedOffOre = false;
		//m_pBase = nullptr;
	};

	bool IsDone() override { return m_DroppedOffOre; };

	bool IsInRange(GOAPAgent* pAgent) override
	{
		return (Elite::Distance(m_pBase->GetPosition(), pAgent->GetPosition()) < 1.f);
	}

	
	bool RequiresInRange() override{return true;};

	bool CheckProceduralPrecondition(GOAPAgent* pAgent, std::vector<GameObject*>* WorldObjects) override
	{
		BaseSpot* closest = nullptr;
		float ClosestDistance = 0.f;
		for (GameObject* ob : (*WorldObjects))
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
		m_pBase = closest;
		m_pTarget = closest;

		return m_pBase != nullptr;
	};

	void PrintActionType() override { std::cout << "DropOffCoalAction, "; }
	~DropOffCoalAction() override = default;
	
	bool Perform(GOAPAgent* pAgent, float dt) override
	{
		m_ElapsedDropOffTime += dt;

		std::cout << "mining..." << std::endl;
		
		if(m_ElapsedDropOffTime > m_DropOffDuration)
		{
			m_pBase->DropOffResources(pAgent);
			m_DroppedOffOre = true;

			std::cout << "Dropped of ore" << std::endl;
		}
		return true;
	}

	void SetBaseSpot(BaseSpot* pBaseSpot) { m_pBase = pBaseSpot; }
	//void SetInRange(bool InRange) override;
	//bool IsInRange() override;;
	
private:
	BaseSpot* m_pBase = nullptr;
	bool m_DroppedOffOre = false;

	float m_DropOffDuration = 1.f;
	float m_ElapsedDropOffTime = 0.f;
 
};

