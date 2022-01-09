#pragma once
#include <map>
#include <queue>
#include <vector>

#include "EIGraph.h"

namespace Elite 
{
	template <class T_NodeType, class T_ConnectionType>
	class BFS
	{
	public:
		BFS(IGraph<T_NodeType, T_ConnectionType>* pGraph);

		std::vector<T_NodeType*> FindPath(T_NodeType* pStartNode, T_NodeType* pDestinationNode);
	private:
		IGraph<T_NodeType, T_ConnectionType>* m_pGraph;
	};

	template <class T_NodeType, class T_ConnectionType>
	BFS<T_NodeType, T_ConnectionType>::BFS(IGraph<T_NodeType, T_ConnectionType>* pGraph)
		: m_pGraph(pGraph)
	{
	}

	template <class T_NodeType, class T_ConnectionType>
	std::vector<T_NodeType*> BFS<T_NodeType, T_ConnectionType>::FindPath(T_NodeType* pStartNode, T_NodeType* pDestinationNode)
	{
		std::queue<T_NodeType*> openList; // frontier
		std::map<T_NodeType*, T_NodeType*> closedList; // all checked nodes

		openList.push(pStartNode); //kick start loop
		
		while(!openList.empty())
		{
			T_NodeType* currentNode = openList.front();
			openList.pop();

			if (currentNode == pDestinationNode)
			{
				break; //exit while loop;

			}

			//At this point we found the goal node
			//track back from goal node to start node to create the path

			// looping over all connections from the current node
			for(auto con : m_pGraph->GetNodeConnections(currentNode))
			{
				T_NodeType* nextNode = m_pGraph->GetNode(con->GetTo());
				if (closedList.find(nextNode) == closedList.end())
				{
					openList.push(nextNode);
					closedList[nextNode] = currentNode;
				}
			}			
		}

		std::vector<T_NodeType*> path;

		T_NodeType* currentNode = pDestinationNode;
		while (currentNode != pStartNode)
		{
			path.push_back(currentNode);
			currentNode = closedList[currentNode];
		}

		path.push_back(pStartNode);
		std::reverse(path.begin(), path.end());
		
		return path;
	}
}

