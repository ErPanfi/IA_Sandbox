#ifndef PUZZLE15SCENE_H
#define PUZZLE15SCENE_H

#include "iscene.h"
#include "PuzzleGraph.h"

class Puzzle15Scene :
	public IScene
{
private:

	PuzzleGraph m_puzzleGraph;

public:
	Puzzle15Scene();
	~Puzzle15Scene();

	virtual void	OnIdle();
	virtual void	OnDraw(sf::RenderWindow&);

};

#endif