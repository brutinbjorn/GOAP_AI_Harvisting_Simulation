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
	~DropOffCoalAction() override = default;

	void Reset() override
	{
		m_DroppedOffOre = false;
		m_pBase = nullptr;
	};

	bool IsDone() override { return m_DroppedOffOre; };

	bool IsInRange(GOAPAgent* pAgent) override;

	bool RequiresInRange() override;

	bool CheckProceduralPrecondition(GOAPAgent* pAgent, std::vector<GameObject*>* WorldObjects) override;

	void PrintActionType() override;

	bool Perform(GOAPAgent* pAgent, float dt) override;

	void SetBaseSpot(BaseSpot* pBaseSpot) { m_pBase = pBaseSpot; }

	
private:
	BaseSpot* m_pBase = nullptr;
	bool m_DroppedOffOre = false;

	float m_DropOffDuration = 1.f;
	float m_ElapsedDropOffTime = 0.f;
 
};

