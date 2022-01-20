#include "MineCoalAction.h"

MineCoalAction::MineCoalAction()
{
	//AddPrecondition("HasTool", true);
	AddPrecondition("HasOre", false);
	AddPrecondition("HasPickAxe", true);
	AddEffect("HasOre", true);
}

void MineCoalAction::Reset()
{
	m_mined = false;
	m_ElapsedMineTime = 0.f;
	m_pTarget = nullptr;
	m_pResourceSpot = nullptr;
}

bool MineCoalAction::IsDone()
{
	return m_mined;
}

bool MineCoalAction::RequiresInRange()
{
	return true;
}

bool MineCoalAction::IsInRange(GOAPAgent* pAgent)
{
	return (Elite::Distance(m_pResourceSpot->GetPosition(), pAgent->GetPosition()) < 1.f);
}

bool MineCoalAction::CheckProceduralPrecondition(GOAPAgent* pAgent, std::vector<GameObject*>* world)
{
	ResourceSpot* closest = nullptr;
	float ClosestDistance = 0.f;
	for (GameObject* ob : *world)
	{
		ResourceSpot* rSpot = dynamic_cast<ResourceSpot*>(ob);
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

	m_pResourceSpot = closest;
	m_pTarget = closest;

	return m_pResourceSpot != nullptr;
}

bool MineCoalAction::Perform(GOAPAgent* pAgent, float dt)
{
	m_ElapsedMineTime += dt;

	if (pAgent->GetRefInventory().ToolType == "ToolPickAxe")
	{
		std::cout << "mining..." << std::endl;
		if (m_ElapsedMineTime > m_MineDuration)
		{
			std::cout << "mining done" << std::endl;
			pAgent->GetRefInventory().m_Resources.emplace_back(ResourceType::coal);

			pAgent->GetRefInventory().m_ToolHealth--;
			if (pAgent->GetRefInventory().m_ToolHealth <= 0)
				pAgent->GetRefInventory().ToolType = "";
			m_mined = true;
		}
		return true;
	}
	return false;
}

void MineCoalAction::PrintActionType()
{
	std::cout << "mineCoalAction, ";
}

void MineCoalAction::SetResourceSpot(ResourceSpot* pResource)
{
	m_pResourceSpot = pResource;
}
