#ifndef ASTAR_PUZZLEGRAPH_H
#define ASTAR_PUZZLEGRAPH_H

#include "PuzzleNode.h"
#include <set>

class PuzzleGraph
{
public:
	//problem definitions
	static const unsigned int BOARD_EDGE_SIZE = 4;
	typedef PuzzleNode<BOARD_EDGE_SIZE> Node;

private:
	Node* m_startingNode;
	Node* m_finalNode;

	void generateStartingAndFinalNode();

	std::set<Node*> m_allocatedNodes;

	friend void Node::buildNeighborsList(std::list<PuzzleNode*>& neighboursList);
	void registerDynamicNode(Node* nodePtr);

public:
	Node* getStartingNode() { return m_startingNode; }
	Node* getFinalNode() { return m_finalNode; }

	PuzzleGraph();

	~PuzzleGraph();
};

#endif