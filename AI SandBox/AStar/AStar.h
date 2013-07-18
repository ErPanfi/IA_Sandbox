#ifndef ASTAR_H
#define ASTAR_H

#include <list>
#include "AStarNode.h"

class AStar
{

private:
	//graph structure
	static const int maxRow = 10;
	static const int maxCol = 10;
	static const int startNodeIdx = 0;
	static const int endNodeIdx = maxRow * maxCol - 1;

	std::list<AStarNode*> openList;

	//starring... the graph
	AStarNode* graphMatrix[maxRow * maxCol];

	//build the graph
	void buildGraph();

	unsigned char				runFlags;

	inline bool setGoalFound(bool newValue)
	{
		if(newValue)
			runFlags |= BITMASK_FOUNDGOAL;
		else
			runFlags &= (~BITMASK_FOUNDGOAL);
	}

public:
	//search for the right path - unnecessary method
	//void run();

	static const unsigned char	BITMASK_RUNFINISHED = 1;
	inline bool runFinished()
	{
		return (runFlags & BITMASK_RUNFINISHED) != 0;
	}
	inline bool setRunFinshed(bool newValue)
	{
		if(newValue)
			runFlags |= BITMASK_RUNFINISHED;
		else
			runFlags &= (~BITMASK_RUNFINISHED);
	}
	
	static const unsigned char	BITMASK_FOUNDGOAL = (BITMASK_RUNFINISHED << 1);
	inline bool goalFound()
	{
		return (runFlags & BITMASK_FOUNDGOAL) != 0;
	}
	//visit next graph node and return the list of the opened ones reached from that
	AStarNode* visitNextNode(std::list<AStarNode*> *openedNodeList);

	//add the current node to the open list by visiting from the specified father
	void openNode(AStarNode* parentNode, AStarNode* currentNode);
	void openNode(AStarNode* parentNode, std::list<AStarNode*> *openedNodeList);	//overload method to add an entire list to open nodes

	//init the graph and return the reference of the start node
	AStarNode* init();
};

#endif //define ASTAR_H 