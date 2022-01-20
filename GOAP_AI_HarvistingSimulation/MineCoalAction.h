#pragma once
#include "Actions.h"

#include "EBFS.h"
#include "ResourceSpot.h"

class MineCoalAction :public Action
{
public:
	MineCoalAction();

	void Reset() override;

	bool IsDone() override;

	bool RequiresInRange() override;

	bool IsInRange(GOAPAgent* pAgent) override;

	bool CheckProceduralPrecondition(GOAPAgent* pAgent, std::vector<GameObject*>* world) override;

	bool Perform(GOAPAgent* pAgent, float dt) override;

	void PrintActionType() override;;

	void SetResourceSpot(ResourceSpot* pResource);;

private:
	bool m_mined = false;
	ResourceSpot* m_pResourceSpot = nullptr;
	float m_MineDuration = 2.f;
	float m_ElapsedMineTime = 0.f;
	
};


