#ifndef ASTAR_CPP_H
#define ASTAR_CPP_H

#include <iostream>
#include "AStar.h"

// old version methods
/*
//AStarNode* AStar::init()
//{
//	//build the graph
//	buildGraph();
//
//	//start from... The start :-)
//	openList.push_front(graphMatrix[startNodeIdx]);
//
//	return graphMatrix[startNodeIdx];
//}
//

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

//void AStar::buildGraph()
//{
//	std::cout << "Building the graph!\n";
//	int i = 0;
//	bool insertNode[] = {
//			true, false, false, false, false, false, false, false, false, false,	//0
//			true, true, true, true, true, true, true, true, true, true,				//1
//			true, false, false, false, false, false, false, false, false, true,		//2
//			true, false, true, true, true, false, true, true, true, true,			//3
//			true, false, true, false, true, false, true, false, true, true,			//4
//			true, false, true, false, true, false, true, false, true, true,			//5
//			true, false, true, false, true, false, true, false, true, true,			//6
//			true, false, true, false, true, false, true, false, true, true,			//7
//			true, false, true, false, true, false, true, false, true, true,			//8
//			true, true, true, false, true, true, true, false, true, true			//9
//						};
//
//	for(int currRow = 0; currRow < maxRow; currRow++)
//	{
//		for(int currCol = 0; currCol < maxCol; currCol++)
//		{
//			AStarNode* currNode;
//
//			currNode = new AStarNode(currRow, currCol, insertNode[i]);
//			std::cout << "Node(" << currRow << ", " << currCol << ") - ";
//
//			graphMatrix[i++] = currNode;
//		}
//		std::cout << "\n";
//	}
//
//	std::cout << "Graph built!\nNow computing adjacency list\n";
//
//	i = 0;
//	for(int currRow = 0; currRow < maxRow; currRow++)
//	{
//		for(int currCol = 0; currCol < maxCol; currCol++)
//		{
//			//obtained current node
//			AStarNode* currNode = graphMatrix[currRow * maxCol + currCol];
//
//			if(currNode != NULL && currNode -> isTransitable())
//			{
//				//heuristic distance is already known, so you can compile it
//				currNode -> HValue = std::abs(graphMatrix[endNodeIdx] -> getRow() - currRow) + std::abs(graphMatrix[endNodeIdx] -> getCol() - currCol);
//
//				std::cout << "Adj(" << currRow << ", " << currCol << ")";
//				for(int rowOffset = -1; rowOffset <= 1; rowOffset+=2)
//				{
//					//The pointed node is really adjacent to current node? Check if...
//					if(	currRow + rowOffset >= 0 &&		//the designed row index is legal
//						currRow + rowOffset < maxRow	
//					  )
//					{
//						AStarNode* targetNode = graphMatrix[(currRow + rowOffset) * maxCol + currCol];
//						if(targetNode != NULL && targetNode -> isTransitable())
//						{
//							currNode->adjacentNodes.push_back(targetNode);
//						}
//					}
//				}
//
//				for(int colOffset = -1; colOffset <= 1; colOffset++)
//				{
//					//The pointed node is really adjacent to current node? Check if...
//					if(	colOffset != 0 &&				//the current node is not adjacent to itself
//						currCol + colOffset >= 0 && 
//						currCol + colOffset < maxCol   	//the designed col index is legal
//						)
//					{
//						AStarNode* targetNode = graphMatrix[currRow * maxCol + currCol + colOffset];
//						if(targetNode != NULL && targetNode -> isTransitable())
//						{
//							currNode->adjacentNodes.push_back(targetNode);
//						}
//					}
//				}
//				std::cout << " - ";
//			}
//		}
//		std::cout << "\n";
//	}
//
//	std::cout << "Adjacency lists compiled\n";
//}
//
//
//void AStar::openNode(AStarNode* parentNode, AStarNode* currentNode)
//{
//	if(currentNode == NULL || !currentNode -> isTransitable())
//	{
//		return;
//	}
//
//	std::cout << "Opening node (" << currentNode -> getRow() << ", " << currentNode -> getCol() << ") : ";
//
//	if(currentNode -> isVisited())
//	{
//		if(currentNode -> GValue <= parentNode -> GValue + 1)
//		{
//			std::cout << "Already visited\n";
//			return;	//do not add it to the list
//		}
//	}
//	else if(currentNode -> isOpen())
//	{
//		if(currentNode -> GValue <= parentNode -> GValue + 1)
//		{
//			std::cout << "Already opened\n";
//			return;	//do not add it to the list
//		}
//	}
//
//	//fill current node data on opening
//	currentNode -> parent  = parentNode;
//	currentNode -> setOpen(true);
//	currentNode -> GValue = parentNode == NULL ? 0 : parentNode -> GValue + 1;
//	
//	//add to open list
//	bool inserted = false;
//	std::list<AStarNode*>::iterator endIter = openList.end();
//	for(std::list<AStarNode*>::iterator iterator = openList.begin(); !inserted && iterator != endIter; iterator++)
//	{
//		AStarNode* iterNode = *iterator;
//
//		if(currentNode -> HValue + currentNode -> GValue < iterNode -> HValue + iterNode -> GValue)
//		{
//			openList.insert(iterator, currentNode);
//			inserted = true;
//		}
//	}
//	if(!inserted)
//	{
//		openList.push_back(currentNode);
//	}
//
//	std::cout << "opened and added.\n";
//}
//
//AStarNode* AStar::visitNextNode(std::list<AStarNode*> *openedNodeList)
//{
//	//pop current node from open list
//	if(openList.empty())	//if empty no path exists
//		return NULL;	
//
//	AStarNode* currentNode = openList.front();
//	openList.pop_front();
//	currentNode -> setVisited(true);
//	std::cout << "Visiting Node(" << currentNode -> getRow() << ", " << currentNode -> getCol() << ")...\n";
//
//	if(currentNode != graphMatrix[endNodeIdx])
//	{
//		//add adjacent nodes to open list
//		std::list<AStarNode*>::iterator adjListEndIter = currentNode -> adjacentNodes.end();
//		for(std::list<AStarNode*>::iterator iter = currentNode -> adjacentNodes.begin(); iter != adjListEndIter; iter++)
//		{
//			AStarNode* openedNode = *iter;
//			if(!(openedNode -> isVisited() || openedNode -> isOpen()) || openedNode -> GValue > currentNode -> GValue + 1)
//			{
//				openedNode -> setVisited(false);
//				openedNodeList -> push_back(openedNode);
//			}
//		}
//	}
//
//	//return the popped node
//	return currentNode;
//}
*/

template <class T, bool NODE_OWN_CONTENT>
AStar<T, NODE_OWN_CONTENT>::~AStar()
{
	std::cout << "Deleting AStar object with " << AStar::Node::s_countNodes << " allocated nodes..." << std::endl;
	for(NodeSet::iterator iter = m_frontier.begin(); iter != m_frontier.end(); ++iter)
	{
		if(NODE_OWN_CONTENT)
		{
			T* targetPtr = &((*iter) -> getContent());
			delete targetPtr;
		}

		delete *iter;
	}

	for(NodeSet::iterator iter = m_openedNodes.begin(); iter != m_openedNodes.end(); ++iter)
	{
		if(NODE_OWN_CONTENT)
		{
			T* targetPtr = &((*iter) -> getContent());
			delete targetPtr;
		}
		delete *iter;
	}

	std::cout << "Deleted. Remaining " << AStar::Node::s_countNodes << " allocated nodes." << std::endl;
}


template <class T, bool NODE_OWN_CONTENT>
AStarNode<T> *AStar<T, NODE_OWN_CONTENT>::decideNextNodeToExplore()
{
	//NodeSet is an ordered set
	NodeSet::iterator iter = m_frontier.begin();
	
	if(iter == m_frontier.end())
		return NULL;

	Node* ret = *iter;
	m_frontier.erase(iter);
	ret -> setFrontiered(false);

	return ret;
}

template <class T, bool NODE_OWN_CONTENT>
void AStar<T, NODE_OWN_CONTENT>::openNode(Node* targetNode, NodeList& frontieredNodeList)
{
	//add node to opened set (already removed from frontier)
	targetNode -> setOpen(true);
	m_openedNodes.insert(targetNode);

	typedef std::list<T*> NeighList;
	NeighList nodeNeighbours;
	targetNode -> getContent().buildNeighborsList(nodeNeighbours);	//the state knows its neighbours

	for(NeighList::iterator iter = nodeNeighbours.begin(); iter != nodeNeighbours.end(); ++iter)
	{
		//new frontier node ptr
		Node* frontierNode = new AStarNode<T>(**iter, targetNode, (*iter) -> computeHValue());

		//search in already opened nodes if this is already present
		/* strange behaviour in set::find, trying a manual scan
		NodeSet::iterator findIter = m_openedNodes.find(frontierNode);
		*/

		NodeSet::iterator findIter;
		for(findIter = m_openedNodes.begin(); findIter != m_openedNodes.end() && (*findIter) -> getContent() != frontierNode -> getContent(); ++findIter);

		if(findIter != m_openedNodes.end())
		{
			//if its GValue it's greater than the new frontier node it must be updated, removed from the already visited nodes list and added to frontiered nodes list
			if(frontierNode -> totalDistance() < (*findIter) -> totalDistance())
			{
				(*findIter) -> setGValue(frontierNode -> getGValue());
				(*findIter) -> setParent(frontierNode -> getParent());
				(*findIter) -> setFrontiered(true);
				(*findIter) -> setOpen(false);

				//add node to the newly-opened list
				frontieredNodeList.push_back(*findIter);

				//remove it from visited list
				m_openedNodes.erase(findIter);
			}	//otherwise it must stay into the visited set

			delete frontierNode;	//discard the created node
		}
		else	//if not visited it must be searched in frontier, for the same purpose
		{
			/*	strange behaviour in set:find, try a manual scan
			findIter = m_frontier.find(frontierNode);
			*/

			for(findIter = m_frontier.begin();findIter != m_frontier.end() && (*findIter) -> getContent() != frontierNode -> getContent(); ++findIter);

			if(findIter != m_frontier.end())
			{
				//if found check if must be updated
				//if its GValue it's greater than the new frontier node it must be updated, but it's already frontiered
				if(frontierNode -> totalDistance() < (*findIter) -> totalDistance())
				{
					(*findIter) -> setGValue(frontierNode -> getGValue());
					(*findIter) -> setParent(frontierNode -> getParent());
				}	//otherwise it must stay into the frontier set

				delete frontierNode;	//discard the created node
			}
			else //never found: the new node can be inserted directly into frontiered set
			{
				frontierNode -> setFrontiered(true);
				frontierNode -> setOpen(false);
				m_frontier.insert(frontierNode);
				//add node to the newly-opened list
				frontieredNodeList.push_back(frontierNode);
			}
		}
	}
}

#endif