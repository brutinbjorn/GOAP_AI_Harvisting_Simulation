#pragma once
#include "Actions.h"
#include "BaseSpot.h"

class PickUpPickAxeAction :
    public Action
{
public:
	PickUpPickAxeAction();

	void Reset() override;

	bool IsDone() override;

	bool RequiresInRange() override;;

	bool IsInRange(GOAPAgent* pAgent) override;

	bool CheckProceduralPrecondition(GOAPAgent* pAgent, std::vector<GameObject*>* world) override;;

	bool Perform(GOAPAgent* pAgent, float dt) override;

	void PrintActionType() override;

	void SetBaseSpot(BaseSpot* pResource);

private:
	bool m_PickedUp = false;
	BaseSpot* m_pBaseSpot = nullptr;
};

