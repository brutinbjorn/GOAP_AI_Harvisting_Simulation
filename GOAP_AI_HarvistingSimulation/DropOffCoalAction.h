#pragma once
#include "Actions.h"
#include "BaseSpot.h"


class DropOffCoalAction :
    public Action
{
public:
	DropOffCoalAction() {
		AddPrecondition("hasOre", true); // can't drop off ore if we don't already have some
		AddEffect("hasOre", false); // we now have no ore
		AddEffect("collectOre", true); // we collected ore
	}


	
	void Reset() override
	{
		m_DroppedOffOre = false;
		m_Base = nullptr;
	};

	bool IsDone() override { return m_DroppedOffOre; };

	bool RequiresInRange() override{return true;};

	bool CheckProceduralPrecondition(GOAPAgent* pAgent, std::vector<GameObject*>* WorldObjects) override
	{
		BaseSpot* closest = nullptr;
		float ClosestDistance = 0.f;
		for (GameObject* ob : (*WorldObjects))
		{
			BaseSpot* rSpot = static_cast<BaseSpot*>(ob);
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
		m_Base = closest;
		m_pTarget = closest;

		return m_Base != nullptr;
	};

	void PrintActionType() override { std::cout << "DropOffCoalAction, "; }
	~DropOffCoalAction() override = default;
	
	bool Perform(GOAPAgent* pAgent, float dt) override
	{
		m_ElapsedDropOffTime += dt;

		if(m_ElapsedDropOffTime > m_DropOffDuration)
		{
			m_Base->DropOffResources(pAgent);
			m_DroppedOffOre = true;
		}
		return true;
	}
	
	//void SetInRange(bool InRange) override;
	//bool IsInRange() override;;
	
private:
	BaseSpot* m_Base = nullptr;
	bool m_DroppedOffOre = false;

	float m_DropOffDuration = 1.f;
	float m_ElapsedDropOffTime = 0.f;
 
};

