#include "DropOffCoalAction.h"

bool DropOffCoalAction::IsInRange(GOAPAgent* pAgent)
{
	return (Elite::Distance(m_pBase->GetPosition(), pAgent->GetPosition()) < 1.f);
}

bool DropOffCoalAction::RequiresInRange()
{
	return true;
}

bool DropOffCoalAction::CheckProceduralPrecondition(GOAPAgent* pAgent, std::vector<GameObject*>* WorldObjects)
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
}

void DropOffCoalAction::PrintActionType()
{
	std::cout << "DropOffCoalAction, ";
}

bool DropOffCoalAction::Perform(GOAPAgent* pAgent, float dt)
{
	m_ElapsedDropOffTime += dt;

	std::cout << "dropping..." << std::endl;

	if (m_ElapsedDropOffTime > m_DropOffDuration)
	{
		m_pBase->DropOffResources(pAgent);
		m_DroppedOffOre = true;

		std::cout << "Dropped of ore" << std::endl;
	}
	return true;
}
