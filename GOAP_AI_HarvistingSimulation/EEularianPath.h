#pragma once
#include <stack>

namespace Elite
{
	enum class Eulerianity
	{
		notEulerian, //no trail
		semiEulerian, // a trail
		eulerian, // a cycle
	};

	template <class T_NodeType, class T_ConnectionType>
	class EulerianPath
	{
	public:

		EulerianPath(IGraph<T_NodeType, T_ConnectionType>* pGraph);

		Eulerianity IsEulerian() const;
		vector<T_NodeType*> FindPath(Eulerianity& eulerianity) const;

	private:
		void VisitAllNodesDFS(int startIdx, vector<bool>& visited) const;
		bool IsConnected() const;

		IGraph<T_NodeType, T_ConnectionType>* m_pGraph;
	};

	template<class T_NodeType, class T_ConnectionType>
	inline EulerianPath<T_NodeType, T_ConnectionType>::EulerianPath(IGraph<T_NodeType, T_ConnectionType>* pGraph)
		: m_pGraph(pGraph)
	{
	}

	template<class T_NodeType, class T_ConnectionType>
	inline Eulerianity EulerianPath<T_NodeType, T_ConnectionType>::IsEulerian() const
	{
		// If the graph is not connected, there can be no Eulerian Trail
		if (IsConnected() == false)
			return Eulerianity::notEulerian;

		// Count nodes with odd degree 
		auto activeNodes = m_pGraph->GetAllActiveNodes();
		int oddCount = 0;
		for (auto node : activeNodes)
		{
			auto connections = m_pGraph->GetNodeConnections(node);
			if (connections.size() & 1)
				++oddCount;
		}
		// A connected graph with more than 2 nodes with an odd degree (an odd amount of connections) is not Eulerian
		if (oddCount > 2)
			return Eulerianity::notEulerian;
		// A connected graph with exactly 2 nodes with an odd degree is Semi-Eulerian (unless there are only 2 nodes)
		// An Euler trail can be made, but only starting and ending in these 2 nodes
		if (oddCount == 2)
			return Eulerianity::semiEulerian;
		// A connected graph with no odd nodes is Eulerian
		
		return Eulerianity::eulerian;
		//return Eulerianity::notEulerian; // REMOVE AFTER IMPLEMENTING
	}

	template<class T_NodeType, class T_ConnectionType>
	inline vector<T_NodeType*> EulerianPath<T_NodeType, T_ConnectionType>::FindPath(Eulerianity& eulerianity) const
	{
		// Get a copy of the graph because this algorithm involves removing edges
		auto graphCopy = m_pGraph->Clone();
		int nrOfNodes = graphCopy->GetNrOfNodes();
		auto path = vector<T_NodeType*>();

		// Check if there can be an Euler path
		auto IsEuler = IsEulerian();
		if (IsEuler != Eulerianity::eulerian)
			return path;
		// If this graph is not eulerian, return the empty path
		// 
		// Else we need to find a valid starting index for the algorithm
		

		// Start algorithm loop
		vector<int> nodeStack;
		vector<int> circuit = vector<int>{};

		int location{ -1 };

		// algorithm...
		for (int i = 0; i < nrOfNodes; i++)
		{
			if (graphCopy->IsNodeValid(i) && (graphCopy->GetNodeConnections(i).size() & 1))
			{
				location = i;
				break;
			}
		}

		if (location == -1)
		{
			location = graphCopy->GetNrOfNodes() - 1; // select last node in the list
		}

		//loop
		do
		{
			if (graphCopy->GetNodeConnections(location).size() == 0)
			{
				circuit.push_back(location);
				location = nodeStack.back();
				nodeStack.pop_back();
			}
			else
			{
				int from{ -1 };
				int to{ -1 };
				nodeStack.push_back(location);
				for (auto i : graphCopy->GetNodeConnections(location))
				{
					from = i->GetFrom();
					to = i->GetTo();
					break;
				}
				if (from == location)
				{
					location = to;
				}
				else
				{
					location = from;
				}
				graphCopy->RemoveConnection(from, to);
			}

		} while (graphCopy->GetNodeConnections(location).size() != 0 || nodeStack.size() != 0);


		circuit.push_back(location);
		for (auto it = circuit.rbegin(); it != circuit.rend(); ++it)
		{
			path.push_back(graphCopy->GetNode(*it));
		}
		
		return path;
	}

	template<class T_NodeType, class T_ConnectionType>
	inline void EulerianPath<T_NodeType, T_ConnectionType>::VisitAllNodesDFS(int startIdx, vector<bool>& visited) const
	{
		// mark the visited node
		visited[startIdx] = true;
		
		// recursively visit any valid connected nodes that were not visited before
		for (T_ConnectionType* pConnection : m_pGraph->GetNodeConnections(startIdx))
			if (visited[pConnection->GetTo()] == false)
				VisitAllNodesDFS(pConnection->GetTo(), visited);

	}

	template<class T_NodeType, class T_ConnectionType>
	inline bool EulerianPath<T_NodeType, T_ConnectionType>::IsConnected() const
	{

		auto ActiveNodes = m_pGraph->GetAllActiveNodes();
		vector<bool> visited(m_pGraph->GetNrOfNodes(), false);
		// find a valid starting node that has connections
		int connectedIdx = invalid_node_index;
		for(auto node: ActiveNodes)
		{
			auto connections = m_pGraph->GetNodeConnections(node);
			if(connections.size() != 0)
			{
				connectedIdx = node->GetIndex();
				break;
			}
		}
		// if no valid node could be found, return false
		if(connectedIdx == invalid_node_index)
			return false;
		
		// start a depth-first-search traversal from the node that has at least one connection
		VisitAllNodesDFS(connectedIdx, visited);
		// if a node was never visited, this graph is not connected
		for (auto node : ActiveNodes)
			if (visited[node->GetIndex()] == false)
				return false;

		return true;
	}

}