#include <iostream>
#include "AStar.h"

AStarNode* AStar::init()
{
	//build the graph
	buildGraph();

	//start from... The start :-)
	openList.push_front(graphMatrix[startNodeIdx]);

	return graphMatrix[startNodeIdx];
}

// unnecessary method
/*
//void AStar::run()
//{
//	//now search the first node of the list
//	for(; currNode != graphMatrix[endNodeIdx] && !openList.empty(); currNode = visitNextNode());
//
//	//if the end node hasn't been reached there's no explicit path
//	if(currNode == graphMatrix[endNodeIdx])
//	{
//		std::list<AStarNode*> pathNodeList;
//		while(currNode != NULL)
//		{
//			pathNodeList.push_front(currNode);
//			currNode = currNode -> parent;
//		}
//
//		while(!pathNodeList.empty())
//		{
//			currNode = pathNodeList.front();
//			std::cout << "(" << currNode -> getRow() << "," << currNode -> getCol() << ")->";
//			pathNodeList.pop_front();
//		}
//
//		std::cout << "End node reached.\n";
//	}
//	else
//	{
//		std::cout << "No path found!\n";
//	}
//}
*/

void AStar::buildGraph()
{
	std::cout << "Building the graph!\n";
	int i = 0;
	bool insertNode[] = {
			true, false, false, false, false, false, false, false, false, false,	//0
			true, true, true, true, true, true, true, true, true, true,				//1
			true, false, false, false, false, false, false, false, false, true,		//2
			true, false, true, true, true, false, true, true, true, true,			//3
			true, false, true, false, true, false, true, false, true, true,			//4
			true, false, true, false, true, false, true, false, true, true,			//5
			true, false, true, false, true, false, true, false, true, true,			//6
			true, false, true, false, true, false, true, false, true, true,			//7
			true, false, true, false, true, false, true, false, true, true,			//8
			true, true, true, false, true, true, true, false, true, true			//9
						};

	for(int currRow = 0; currRow < maxRow; currRow++)
	{
		for(int currCol = 0; currCol < maxCol; currCol++)
		{
			AStarNode* currNode;

			currNode = new AStarNode(currRow, currCol, insertNode[i]);
			std::cout << "Node(" << currRow << ", " << currCol << ") - ";

			graphMatrix[i++] = currNode;
		}
		std::cout << "\n";
	}

	std::cout << "Graph built!\nNow computing adjacency list\n";

	i = 0;
	for(int currRow = 0; currRow < maxRow; currRow++)
	{
		for(int currCol = 0; currCol < maxCol; currCol++)
		{
			//obtained current node
			AStarNode* currNode = graphMatrix[currRow * maxCol + currCol];

			if(currNode != NULL && currNode -> isTransitable())
			{
				//heuristic distance is already known, so you can compile it
				currNode -> HValue = std::abs(graphMatrix[endNodeIdx] -> getRow() - currRow) + std::abs(graphMatrix[endNodeIdx] -> getCol() - currCol);

				std::cout << "Adj(" << currRow << ", " << currCol << ")";
				for(int rowOffset = -1; rowOffset <= 1; rowOffset+=2)
				{
					//The pointed node is really adjacent to current node? Check if...
					if(	currRow + rowOffset >= 0 &&		//the designed row index is legal
						currRow + rowOffset < maxRow	
					  )
					{
						AStarNode* targetNode = graphMatrix[(currRow + rowOffset) * maxCol + currCol];
						if(targetNode != NULL && targetNode -> isTransitable())
						{
							currNode->adjacentNodes.push_back(targetNode);
						}
					}
				}

				for(int colOffset = -1; colOffset <= 1; colOffset++)
				{
					//The pointed node is really adjacent to current node? Check if...
					if(	colOffset != 0 &&				//the current node is not adjacent to itself
						currCol + colOffset >= 0 && 
						currCol + colOffset < maxCol   	//the designed col index is legal
						)
					{
						AStarNode* targetNode = graphMatrix[currRow * maxCol + currCol + colOffset];
						if(targetNode != NULL && targetNode -> isTransitable())
						{
							currNode->adjacentNodes.push_back(targetNode);
						}
					}
				}
				std::cout << " - ";
			}
		}
		std::cout << "\n";
	}

	std::cout << "Adjacency lists compiled\n";
}

void AStar::openNode(AStarNode* parentNode, std::list<AStarNode*> *openedNodeList)
{
	std::list<AStarNode*>::const_iterator endIter (openedNodeList -> end());

	for(std::list<AStarNode*>::iterator iter = openedNodeList -> begin(); iter != endIter; ++iter)
	{
		openNode(parentNode, *iter);
	}
}

void AStar::openNode(AStarNode* parentNode, AStarNode* currentNode)
{
	if(currentNode == NULL || !currentNode -> isTransitable())
	{
		return;
	}

	std::cout << "Opening node (" << currentNode -> getRow() << ", " << currentNode -> getCol() << ") : ";

	if(currentNode -> isVisited())
	{
		if(currentNode -> GValue <= parentNode -> GValue + 1)
		{
			std::cout << "Already visited\n";
			return;	//do not add it to the list
		}
	}
	else if(currentNode -> isOpen())
	{
		if(currentNode -> GValue <= parentNode -> GValue + 1)
		{
			std::cout << "Already opened\n";
			return;	//do not add it to the list
		}
	}

	//fill current node data on opening
	currentNode -> parent  = parentNode;
	currentNode -> setOpen(true);
	currentNode -> GValue = parentNode == NULL ? 0 : parentNode -> GValue + 1;
	
	//add to open list
	bool inserted = false;
	std::list<AStarNode*>::iterator endIter = openList.end();
	for(std::list<AStarNode*>::iterator iterator = openList.begin(); !inserted && iterator != endIter; iterator++)
	{
		AStarNode* iterNode = *iterator;

		if(currentNode -> HValue + currentNode -> GValue < iterNode -> HValue + iterNode -> GValue)
		{
			openList.insert(iterator, currentNode);
			inserted = true;
		}
	}
	if(!inserted)
	{
		openList.push_back(currentNode);
	}

	std::cout << "opened and added.\n";
}

AStarNode* AStar::visitNextNode(std::list<AStarNode*> *openedNodeList)
{
	//pop current node from open list
	if(openList.empty())	//if empty no path exists
		return NULL;	

	AStarNode* currentNode = openList.front();
	openList.pop_front();
	currentNode -> setVisited(true);
	std::cout << "Visiting Node(" << currentNode -> getRow() << ", " << currentNode -> getCol() << ")...\n";

	if(currentNode != graphMatrix[endNodeIdx])
	{
		//add adjacent nodes to open list
		std::list<AStarNode*>::iterator adjListEndIter = currentNode -> adjacentNodes.end();
		for(std::list<AStarNode*>::iterator iter = currentNode -> adjacentNodes.begin(); iter != adjListEndIter; iter++)
		{
			AStarNode* openedNode = *iter;
			if(!(openedNode -> isVisited() || openedNode -> isOpen()) || openedNode -> GValue > currentNode -> GValue + 1)
			{
				openedNode -> setVisited(false);
				openedNodeList -> push_back(openedNode);
			}
		}
	}

	//return the popped node
	return currentNode;
}
