#ifndef PUZZLE15SCENE_H
#define PUZZLE15SCENE_H

#include "iscene.h"
#include "PuzzleGraph.h"
#include "AStar\AStar.h"

class Puzzle15Scene :
	public IScene
{
public:
	//flags management
	typedef unsigned char SceneBitmask;
	static const SceneBitmask EMPTY_BITMASK = 0;

	//astar definitions
	typedef AStar<PuzzleGraph::Node, false> AStarSolver;

	//rendering frame timelapse
	static const unsigned long RENDERING_PAUSE_MILLIS = 1000;
private:

	PuzzleGraph m_puzzleGraph;
	SceneBitmask m_flags;

	unsigned int m_openedNodes;
	unsigned int m_frontierNodes;

	AStarSolver m_solver;
	AStarSolver::Node* m_currAStarNode;
	AStarSolver::NodeList m_nodeList;

	//rendering goal path frames
	sf::Clock m_clock;
	unsigned long m_lastGoalFrameMillis;
	AStarSolver::NodeList::iterator m_goalPathIterator;
	AStarSolver::Node* m_goalPathNode;
	unsigned int m_goalPathLength;
	const sf::Font *m_font;

public:
	//ctors and dtors
	Puzzle15Scene();
	~Puzzle15Scene();


	//virtual IScene inherited methods
	virtual void	OnIdle();
	virtual void	OnDraw(sf::RenderWindow&);

	//flags methods section

	//goal found flag
	static const SceneBitmask GOAL_FOUND_BITMASK = 1;
	inline bool goalFound() const { return (m_flags & GOAL_FOUND_BITMASK) != EMPTY_BITMASK; }
	inline void setGoalFound(bool newValue)
	{
		if(newValue)
			m_flags |= GOAL_FOUND_BITMASK;
		else
			m_flags &= ~GOAL_FOUND_BITMASK;
	}
};

#endif