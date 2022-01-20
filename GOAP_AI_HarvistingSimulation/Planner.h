#pragma once
#include <map>
#include <string>
#include "GOAPAgent.h"


class Action;

class Planner
{
private:
class Node
{
public:
	Node() = default;
	Node(Node* parent, float cost, std::map<std::string, bool> state, Action* action)
		: pParent(parent), runningCost(cost), state(state), m_Action(action) {};
	~Node() = default;
	Node* pParent = nullptr;
	float runningCost = 0.f;
	std::map<std::string, bool> state{};
	Action* m_Action = nullptr;
};

public:
	Planner(std::vector<GameObject*>* WorldObjects) : m_worldObjects(WorldObjects) {};
	~Planner() = default;
	
	std::list<Action*> Plan(GOAPAgent* agent, std::map<std::string, bool> goal);

private:
	bool InState(std::map<std::string, bool> test, std::map<std::string, bool> states);
	bool BuildGraph(Node* Parent,std::vector<Node*>& leaves,std::vector<Action*> usableActions, std::map<std::string,bool> goal);

	std::vector<Action*> ActionSubset(std::vector<Action*> actions, Action* removeMe);
	
	static std::map<std::string, bool> PopulateState( const std::map<std::string,bool>& CurrentState, const std::map<std::string,bool>& StateChange);
	
	std::vector<GameObject*>* m_worldObjects = nullptr;

	std::vector<Node*> m_Nodes;

};
	


