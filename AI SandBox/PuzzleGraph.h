#ifndef ASTAR_PUZZLEGRAPH_H
#define ASTAR_PUZZLEGRAPH_H

#include "PuzzleNode.h"

class PuzzleGraph
{
public:
	//problem definitions
	static const unsigned int BOARD_EDGE_SIZE = 3;
	typedef PuzzleNode<BOARD_EDGE_SIZE> Node;

private:
	Node* m_startingNode;
	Node* m_finalNode;

	void generateStartingAndFinalNode();

public:
	Node* getStartingNode() { return m_startingNode; }
	Node* getFinalNode() { return m_finalNode; }

	PuzzleGraph();

	~PuzzleGraph();
};

#endif