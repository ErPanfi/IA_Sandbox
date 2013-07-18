#ifndef GAMESCENE_H
#define GAMESCEN_H

#include "IScene.h"

class Agent;

class GameScene : public IScene
{
public:
	GameScene();
	virtual ~GameScene();

	virtual void	OnIdle();
	virtual void	OnDraw(sf::RenderWindow&);

private:
	Agent* m_agent;

};
#endif
