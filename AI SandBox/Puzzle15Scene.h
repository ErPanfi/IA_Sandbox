#ifndef PUZZLE15SCENE_H
#define PUZZLE15SCENE_H

#include "iscene.h"

class Puzzle15Scene :
	public IScene
{
public:
	Puzzle15Scene() {};
	~Puzzle15Scene() {};

	virtual void	OnIdle();
	virtual void	OnDraw(sf::RenderWindow&);

};

#endif