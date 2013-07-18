#include <iostream>
#include "AStarScene.h"

AStarScene::AStarScene()
{
	/*
	aStar = new AStar();	
	std::cout << "Built object." << std::endl;
	*/
}

void AStarScene::OnIdle()
{
	/*
	if(!aStar -> runFinished())
	{
		visitedNode = aStar -> visitNextNode(&openedNodes);
	}
	*/
}

void AStarScene::OnDraw(sf::RenderWindow&)
{
	/*
	if(!aStar -> runFinished())
	{
		if(visitedNode == NULL)
		{
			aStar -> setRunFinshed(true);
			std::cout << "No path exists.";
		}
		else if(!visitedNode -> isOpen())
		{
			aStar -> openNode(visitedNode, &openedNodes);
		}
		else if(visitedNode -> is
	*/
}