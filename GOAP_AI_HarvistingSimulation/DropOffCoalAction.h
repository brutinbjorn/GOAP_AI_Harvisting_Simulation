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
		DroppedOffOre = false;
		m_Base = nullptr;
	};

	bool IsDone() override { return DroppedOffOre; };

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

	void PrintActionType() override { std::cout << "DropOffCoalAction, "; };
	
private:
	BaseSpot* m_Base = nullptr;
	bool DroppedOffOre = false;
 
};

