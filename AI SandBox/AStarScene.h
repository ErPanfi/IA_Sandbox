#ifndef ASTAR_SCENE_H
#define ASTAR_SCENE_H

#include <list>
#include "IScene.h"
#include "AStar\AStar.h"

class AStarScene : public IScene
{
public:
	AStarScene();
	~AStarScene() {};

	virtual void	OnIdle();
	virtual void	OnDraw(sf::RenderWindow&);

private:
	AStar*					aStar;
	std::list<AStarNode*>	openedNodes;
	AStarNode*				visitedNode;
};

#endif