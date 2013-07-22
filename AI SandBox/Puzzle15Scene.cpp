#include "Puzzle15Scene.h"

Puzzle15Scene::Puzzle15Scene()
{
	m_puzzleGraph.getStartingNode().echoBoard();
}

Puzzle15Scene::~Puzzle15Scene()
{
}

void Puzzle15Scene::OnIdle()
{
}

void Puzzle15Scene::OnDraw(sf::RenderWindow& renderWin)
{
	m_puzzleGraph.getStartingNode().drawOnScreen(renderWin);
}
