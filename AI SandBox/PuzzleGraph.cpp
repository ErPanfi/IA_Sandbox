#include "PuzzleGraph.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

void PuzzleGraph::generateStartingAndFinalNode()
{
	//init random number generator
	srand((unsigned int)(time(NULL)));

	unsigned int startingBoard[Node::BOARD_SIZE];

	for(int i = 1; i < Node::BOARD_SIZE; ++i)
		startingBoard[i - 1] = i;

	//finally add the empty cell. This is the final board
	startingBoard[Node::BOARD_SIZE - 1] = Node::EMPTY_SPACE;

	m_finalNode = new Node(startingBoard, this);
	m_allocatedNodes.insert(m_finalNode);

	//now Fisher�Yates shuffle
	for(int i = 0; i < Node::BOARD_SIZE - 3; ++i)
	{
		unsigned int swapPos = rand() % (Node::BOARD_SIZE - 1);
		unsigned int tmp = startingBoard[swapPos];
		startingBoard[swapPos] = startingBoard[i];
		startingBoard[i] = tmp;
	}

	//count inversions and detect if they're even
	unsigned int inversions = 0;
	for(int i = 0; i < Node::BOARD_SIZE - 2; ++i)
	{
		for(int j = i + 1; j < Node::BOARD_SIZE - 1; ++j)
		{
			if(startingBoard[i] > startingBoard[j])
				++inversions;
		}
	}

	//if there are an odd number of inversions then exchange the last two values
	if(inversions % 2)
	{
		unsigned int tmp = startingBoard[Node::BOARD_SIZE - 2];
		startingBoard[Node::BOARD_SIZE - 2] = startingBoard[Node::BOARD_SIZE - 3];
		startingBoard[Node::BOARD_SIZE - 3] = tmp;
	}

	m_startingNode = new Node(startingBoard, this);
	m_allocatedNodes.insert(m_startingNode);
}

PuzzleGraph::PuzzleGraph()
{
	generateStartingAndFinalNode();
}

PuzzleGraph::~PuzzleGraph()
{
	std::cout << "Starting deleting nodes. There are " << Node::s_nodeCount << " in memory and " << m_allocatedNodes.size() << " registered in set." << std::endl;
	for(std::set<Node*>::iterator iter = m_allocatedNodes.begin(); iter != m_allocatedNodes.end(); ++iter)
	{
		Node* currNode = *iter;
		delete currNode;
	}
	std::cout << "There are still " << Node::s_nodeCount << " puzzle nodes in memory." << std::endl;
}

void PuzzleGraph::registerDynamicNode(Node* nodePtr)
{
	m_allocatedNodes.insert(nodePtr);
}