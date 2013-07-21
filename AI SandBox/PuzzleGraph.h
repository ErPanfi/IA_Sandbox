#ifndef ASTAR_PUZZLEGRAPH_H
#define ASTAR_PUZZLEGRAPH_H

#include "PuzzleNode.h"

class PuzzleGraph
{
public:
	//problem definitions
	static const unsigned int BOARD_EDGE_SIZE = 4;
	typedef PuzzleNode<BOARD_EDGE_SIZE> Node;

private:
	Node m_startingNode;
public:
	Node& getStartingNode() const { return m_startingNode; }
};

#endif