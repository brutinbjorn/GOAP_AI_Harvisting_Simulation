#include "PickUpPickAxeAction.h"

PickUpPickAxeAction::PickUpPickAxeAction()
{
	AddPrecondition("HasPickAxe", false);
	AddEffect("HasPickAxe", true);
}

void PickUpPickAxeAction::Reset()
{
	m_PickedUp = false;
	m_pBaseSpot = nullptr;
	m_pTarget = nullptr;

}

bool PickUpPickAxeAction::IsDone()
{
	return m_PickedUp;
}

bool PickUpPickAxeAction::RequiresInRange()
{
	return true;
}

bool PickUpPickAxeAction::IsInRange(GOAPAgent* pAgent)
{
	return (Elite::Distance(m_pBaseSpot->GetPosition(), pAgent->GetPosition()) < 1.f);
}

bool PickUpPickAxeAction::CheckProceduralPrecondition(GOAPAgent* pAgent, std::vector<GameObject*>* world)
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
}

bool PickUpPickAxeAction::Perform(GOAPAgent* pAgent, float dt)
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

void PickUpPickAxeAction::PrintActionType()
{
	std::cout << "PickedUpToolAction, ";
}

void PickUpPickAxeAction::SetBaseSpot(BaseSpot* pResource)
{
	m_pBaseSpot = pResource;
}
