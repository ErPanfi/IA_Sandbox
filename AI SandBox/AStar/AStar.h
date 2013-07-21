#ifndef ASTAR_H
#define ASTAR_H

#include <list>
#include <set>
#include "AStarNode.h"

template <class T>
class AStar
{
public:
	typedef AStarNode<T> Node;
	typedef unsigned char AStar_BitMask;
	typedef std::list<Node*> NodeList;

	struct NodePtrLessCompare
	{
		bool operator()(Node* first, Node* second)
		{
			return (*first) < (*second);
		}
	} m_nodeComparator;

	typedef std::set<Node*, NodePtrLessCompare> NodeSet;

	static const AStar_BitMask BITMASK_EMPTY = 0;

private:
	//graph structure
	/*
	static const int maxRow = 10;
	static const int maxCol = 10;
	static const int startNodeIdx = 0;
	static const int endNodeIdx = maxRow * maxCol - 1;

	//starring... the graph
	AStarNode* graphMatrix[maxRow * maxCol];

	//build the graph
	void buildGraph();
	*/

	NodeSet m_frontier;		//these are the frontier nodes
	NodeSet m_openedNodes;	//these are visited nodes

	AStar_BitMask m_runFlags;

	inline bool setGoalFound(bool newValue)
	{
		if(newValue)
			m_runFlags |= BITMASK_FOUNDGOAL;
		else
			m_runFlags &= (~BITMASK_FOUNDGOAL);
	}


	void unInit(); //this must clean the nodes into the sets before object dies

public:

	~AStar();

	static const unsigned char	BITMASK_RUNFINISHED = 1;
	inline bool runFinished()
	{
		return (m_runFlags & BITMASK_RUNFINISHED) != 0;
	}
	inline bool setRunFinshed(bool newValue)
	{
		if(newValue)
			m_runFlags |= BITMASK_RUNFINISHED;
		else
			m_runFlags &= (~BITMASK_RUNFINISHED);
	}
	
	static const unsigned char	BITMASK_FOUNDGOAL = (BITMASK_RUNFINISHED << 1);
	inline bool goalFound()
	{
		return (runFlags & BITMASK_FOUNDGOAL) != 0;
	}

	//visit the given node and add its neighbours to the frontier; the nodes which have been added to the frontier are also added to the given openedNodeList, to notify the caller the frontier variation
	void openNode(Node* targetNode, NodeList& frontieredNodeList);

	//decide next node to explore, remove it from the frontier and returns it. If no nodes are still to be explored returns NULL
	Node* decideNextNodeToExplore();

	//init the graph and return the reference of the start node
	//AStarNode* init();	//don't needed: AStar now doesn't know graph structure

	//gives iterator to the two nodes list
	inline void getFrontierNodesIterators(typename NodeSet::iterator &beginIter, typename NodeSet::iterator &endIter) const 
	{ 
		beginIter = m_frontier.begin(); 
		endIter = m_frontier.end();
	}

	inline void getOpenNodesIterators(typename NodeSet::iterator &beginIter, typename NodeSet::iterator &endIter) const 
	{ 
		beginIter = m_openedNodes.begin(); 
		endIter = m_openedNodes.end();
	}
};

#include "AStar_cpp.h"

#endif //define ASTAR_H 
