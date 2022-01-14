#include "Planner.h"

#include <iostream>


#include "Actions.h"


std::vector<Action*> Planner::plan(GOAPAgent* agent, 
    std::map<std::string, bool> goal)
{
	// get all possible actions the agent can perform
	std::vector<Action*> actions = agent->GetAllActions();

	// get the world state from all objects that have a influence on the world(only the agent right now)
	//TODO expand Maybe;
	std::map<std::string, bool> worldState = agent->GetWorldState();


	// reset all the actions that the agent can do (action info should change depending on agent current abilitys, IE hastool? for example)
	for (auto *element : actions)
	{
		element->Reset();
	}

	// check for all the actions that actually can change the world.(cant pick a rock if there are no rocks)
	std::vector<Action*> UsableActions;
	for(auto *element : actions)
	{
		if (element->CheckProceduralPrecondition(agent, m_worldObjects))
			UsableActions.push_back(element);
	}

	// list of linked actions with a pointer to parent and action
	std::vector<Node> leaves;

	//build Graph
	// create a top down chain graph of all actions that perputally
	//change the world state until we find one we want to go down
	//
	Node start = Node(nullptr, 0, worldState, nullptr);
	bool succes = BuildGraph(start,leaves,UsableActions,goal);

	if(!succes)
	{
		// no plan.
		std::cout << "NO PLAN" << std::endl;
		return std::vector<Action*>{};
	}

	// get the cheapest leaf
	Node cheapest = leaves[0];
	for (auto leaf : leaves)
	{
		if (leaf.m_RunningCost < cheapest.m_RunningCost)
			cheapest = leaf;
	}

	// get its node and work back through parents, resulting in a list of actions,
	// pointers still looking to agent->actions;
	std::list<Action*> result;
	Node* n = &cheapest;
	while (n != nullptr)
	{
		if(n->m_Action != nullptr)
			result.push_front(n->m_Action);
		n = n->m_Parent;
	}

	
	std::vector<Action*> toReturn;
	for (auto value : result)
	{
		toReturn.push_back(value);
	}

	return toReturn;
	
}

// returns true if all the pairs in test are inside states and are equil
bool Planner::inState(std::map<std::string, bool> test, std::map<std::string, bool> states)
{
	bool AllMatchesFound = true;
	for (auto pair : test)
	{
		bool MatchFound = false;
		for (auto statePair : states)
		{
			if(statePair.first == pair.first && statePair.second == pair.second)
			{
				MatchFound = true;
				break;
			}
		}
		if (!MatchFound)
			AllMatchesFound = false;
	}
	return AllMatchesFound;
}

bool Planner::BuildGraph(Node Parent, std::vector<Node> leaves, std::vector<Action*> usableActions,
                         std::map<std::string, bool> goal)
{
	bool foundOne = false;
	for (auto* action : usableActions)
	{

		//checks if the requirements are fufilled in the parent state
		if(inState(action->GetPreconditions(),Parent.m_State))
		{

			// fufill the effect changes
			std::map<std::string, bool> currentState = PopulateState(Parent.m_State, action->GetEffects());

			Node node =  Node(&Parent, Parent.m_RunningCost + action->GetCost(), currentState, action);

			//check if the goal is fufilled.
			if(inState(goal,currentState))
			{
				// if true, add the result to the leaves and return plan found;
				leaves.push_back(node);
				foundOne = true;
			}
			else
			{
				// copy the list of possible actions except the one we just used 	
				std::vector<Action*> subset = ActionSubset(usableActions, action);

				// restart with copy, going until we went true all possible actions.
				bool found = BuildGraph(node, leaves, subset, goal);
				if (found)
					foundOne = true;
			}
		}
	}
	
	return foundOne;
}

// basicly a copy without the RemoveMe
std::vector<Action*> Planner::ActionSubset(std::vector<Action*> actions, Action* removeMe)
{
	std::vector<Action*> subSet;
	for (auto action : actions)
	{
		if (!(action == removeMe))
			subSet.push_back(action);
	}
	return subSet;
	
	
}
// actionEffects adds and overwrite the currentstate and returns the result in a new list
std::map<std::string, bool> Planner::PopulateState(const std::map<std::string, bool>& CurrentState,
                                                   const std::map<std::string, bool>& ActionEffects)
{

	std::map<std::string, bool> newState;
	
	for (auto pair : CurrentState)
	{
		newState[pair.first] = pair.second;
	}

	for (auto pair : ActionEffects)
	{
		newState[pair.first] = pair.second;
	}

	return newState;
}
