#pragma once
#include "ENavigation.h"

namespace Elite
{
	using namespace std;
	
	template <class T_NodeType, class T_ConnectionType>
	class AStar
	{
	public:
		AStar(IGraph<T_NodeType, T_ConnectionType>* pGraph, Heuristic hFunction);

		// stores the optimal connection to a node and its total costs related to the start and end node of the path
		struct NodeRecord
		{
			T_NodeType* pNode = nullptr;
			T_ConnectionType* pConnection = nullptr;
			float costSoFar = 0.f; // accumulated g-costs of all the connections leading up to this one
			float estimatedTotalCost = 0.f; // f-cost (= costSoFar + h-cost)

			bool operator==(const NodeRecord& other) const
			{
				return pNode == other.pNode
					&& pConnection == other.pConnection
					&& costSoFar == other.costSoFar
					&& estimatedTotalCost == other.estimatedTotalCost;
			};

			bool operator<(const NodeRecord& other) const
			{
				return estimatedTotalCost < other.estimatedTotalCost;
			};
		};

		std::vector<T_NodeType*> FindPath(T_NodeType* pStartNode, T_NodeType* pDestinationNode);

	private:
		float GetHeuristicCost(T_NodeType* pStartNode, T_NodeType* pEndNode) const;

		const IGraph<T_NodeType, T_ConnectionType>* m_pGraph;
		Heuristic m_HeuristicFunction;
	};

	template <class T_NodeType, class T_ConnectionType>
	AStar<T_NodeType, T_ConnectionType>::AStar(IGraph<T_NodeType, T_ConnectionType>* pGraph, Heuristic hFunction)
		: m_pGraph(pGraph)
		, m_HeuristicFunction(hFunction)
	{
	}

	template <class T_NodeType, class T_ConnectionType>
	std::vector<T_NodeType*> AStar<T_NodeType, T_ConnectionType>::FindPath(T_NodeType* pStartNode, T_NodeType* pGoalNode)
	{
		vector<T_NodeType*> path;
		vector<NodeRecord> openList;
		vector<NodeRecord> closedList;
		NodeRecord currentRecord;

		currentRecord.pNode = pStartNode;
		currentRecord.pConnection = nullptr;
		currentRecord.estimatedTotalCost = GetHeuristicCost(pStartNode, pGoalNode);
		openList.push_back(currentRecord);

		// :2
		while(!openList.empty())
		{
			//2.A
			currentRecord = *std::min_element(openList.begin(), openList.end()); // get cheapest node in open list
		
			//2.B
			if (currentRecord.pNode == pGoalNode)
			{
				break;
			}

			//2.C
			for (auto connection : m_pGraph->GetNodeConnections(currentRecord.pNode->GetIndex())) // go over all connection
			{
			
				T_NodeType* pNextNode = m_pGraph->GetNode(connection->GetTo()); // get connected node				
				float gCost = connection->GetCost() + currentRecord.costSoFar; // cost from pstart
				float hCost = GetHeuristicCost(pNextNode, pGoalNode); // estimatated cost
				float fcost = gCost + GetHeuristicCost(pNextNode, pGoalNode); // calc total xost

				auto compareNodes = [pNextNode](const NodeRecord& a) { return (a.pNode == pNextNode); };//lambda
				//
				//2.D
				vector<NodeRecord>::iterator closedRecord;
				//find closed record
				closedRecord = std::find_if(closedList.begin(), closedList.end(), //check if connection node is in closed list
					compareNodes);

				vector<NodeRecord>::iterator openRecord;
				//find open Record
				openRecord = std::find_if(openList.begin(), openList.end(), //check if connection node is in closed list
					compareNodes);

				
				if (closedRecord != closedList.end())
				{
					if (closedRecord->costSoFar >= gCost)
						closedList.erase(closedRecord);
					else continue;
				}
				else if (openRecord != openList.end())
				{
					if (gCost < openRecord->costSoFar)
						openList.erase(openRecord);
					else continue;
				}
				else
				{
					NodeRecord newRecord;
					newRecord.costSoFar = gCost; // cost from start
					newRecord.estimatedTotalCost = fcost; // total
					newRecord.pNode = pNextNode;
					newRecord.pConnection = connection;
					openList.push_back(newRecord);
				}
			} //end connection/ for loop.

			//2.G
			closedList.push_back(currentRecord);
			openList.erase(std::find(openList.begin(), openList.end(), currentRecord));

			if (closedList.size() >= 10000)
			{
				std::cout << " closed list overflowing\n";
				break;
			}
			if (openList.size() >= 10000)
			{
				std::cout << "open list overflowing\n ";
				break;
			}
			
		}
		
		//3
		T_NodeType* pNode = nullptr;
		vector<NodeRecord>::iterator it;

		if (!openList.empty())
		{
			while (pNode != pStartNode)
			{
				path.push_back(currentRecord.pNode);

				it = std::find_if(closedList.begin(), closedList.end(),
					[currentRecord](const NodeRecord& a)
					{if (a.pConnection != nullptr)
					return a.pConnection->GetTo() == currentRecord.pConnection->GetFrom();
				return false;
					});

				if (it != closedList.end())
				{
					currentRecord = *it;
					closedList.erase(it);
				}
				else
				{
					pNode = pStartNode;
				}
			}
			path.push_back(pNode);
			std::reverse(path.begin(), path.end());
		}
		return path;
	}

	template <class T_NodeType, class T_ConnectionType>
	float Elite::AStar<T_NodeType, T_ConnectionType>::GetHeuristicCost(T_NodeType* pStartNode, T_NodeType* pEndNode) const
	{
		Vector2 toDestination = m_pGraph->GetNodePos(pEndNode) - m_pGraph->GetNodePos(pStartNode);
		return m_HeuristicFunction(abs(toDestination.x), abs(toDestination.y));
	}
}
