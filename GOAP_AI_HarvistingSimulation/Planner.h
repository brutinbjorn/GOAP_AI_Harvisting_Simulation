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
		Node(){};
		Node(Node* parent, float cost, std::map<std::string, bool> state, Action* action)
			: m_Parent(parent), m_RunningCost(cost), m_State(state), m_Action(action) {};
		~Node() = default;
		Node* m_Parent = nullptr;
		float m_RunningCost = 0.f;
		std::map<std::string, bool> m_State{};
		Action* m_Action = nullptr;
};

public:
	Planner(std::vector<GameObject*>* WorldObjects) : m_worldObjects(WorldObjects){};
	~Planner() = default;;
	
	std::vector<Action*> plan(GOAPAgent* agent,
		std::map<std::string, bool> goal);

		//virtual bool AddPlan(GOAPAgent* pAgent, std::map<std::string, bool> WorldState) = 0;
private:
	bool inState(std::map<std::string, bool> test, std::map<std::string, bool> states);
	bool BuildGraph(Node Parent,std::vector<Node> leaves,std::vector<Action*> usableActions, std::map<std::string,bool> goal);
	std::vector<Action*> ActionSubset(std::vector<Action*> actions, Action* removeMe);
	
	static std::map<std::string, bool> PopulateState(
		const std::map<std::string,bool>& CurrentState,
		const std::map<std::string,bool>& StateChange);
	
	std::vector<GameObject*>* m_worldObjects = nullptr;



};
	


