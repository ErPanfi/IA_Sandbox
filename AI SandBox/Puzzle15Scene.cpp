#include "Puzzle15Scene.h"
#include "FontManager.h"

Puzzle15Scene::Puzzle15Scene()
	: m_openedNodes(0)
	, m_frontierNodes(0)
	, m_flags(EMPTY_BITMASK)
{
	PuzzleGraph::Node* startingNode = m_puzzleGraph.getStartingNode();
	startingNode -> echoBoard();
	m_currAStarNode = new AStarSolver::Node(*startingNode, nullptr, startingNode -> computeHValue());
	m_clock.restart();
	m_lastGoalFrameMillis = m_clock.getElapsedTime().asMilliseconds();
	m_font = FontManager::Istance() -> GetFont(FontEnum::Font_Cyber);
}

Puzzle15Scene::~Puzzle15Scene()
{
	delete m_currAStarNode;	//delete goal node
}

void Puzzle15Scene::OnIdle()
{
	if(!goalFound())
	{
		m_nodeList.clear();
		m_solver.openNode(m_currAStarNode, m_nodeList);
		++m_openedNodes;
		m_currAStarNode = m_solver.decideNextNodeToExplore();
		m_frontierNodes += m_nodeList.size() - 1;
		if(m_currAStarNode -> getContent() == *m_puzzleGraph.getFinalNode())
		{
			setGoalFound(true);
			AStarSolver::Node* backtracker = m_currAStarNode;
			m_nodeList.clear();

			while(backtracker)
			{
				m_nodeList.push_front(backtracker);
				backtracker = backtracker -> getParent();
			}

			m_goalPathLength = m_nodeList.size() - 1;
			m_goalPathIterator = m_nodeList.begin();
			m_goalPathNode = *m_goalPathIterator;
			++m_goalPathIterator;
		}
	}
}

void Puzzle15Scene::OnDraw(sf::RenderWindow& renderWin)
{
	if(!goalFound())
	{
		std::stringstream statusStringStream;
		statusStringStream << "Working!" << std::endl << "Opened nodes : " << m_openedNodes << std::endl << "Frontier nodes: " << m_frontierNodes;
		std::string statusString(statusStringStream.str());
		sf::Text statusText(statusString, *m_font, 45U);
		statusText.setPosition(3.0f * PuzzleGraph::Node::SQUARE_HORIZ_PADDING_PX, 3.0f * PuzzleGraph::Node::SQUARE_VERT_PADDING_PX);
		statusText.setColor(sf::Color::Black);
		renderWin.draw(statusText);
	}
	else
	{
		std::stringstream statusStringStream;
		statusStringStream << "Steps remaining : " << m_goalPathLength;
		std::string statusString(statusStringStream.str());
		sf::Text statusText(statusString, *m_font, 45U);
		statusText.setPosition(PuzzleGraph::Node::SQUARE_HORIZ_PADDING_PX, 2.0f * PuzzleGraph::Node::SQUARE_VERT_PADDING_PX);
		statusText.setColor(sf::Color::Black);
		renderWin.draw(statusText);
		m_goalPathNode -> getContent().drawOnScreen(renderWin, statusText.getLocalBounds().height + 4.0f * PuzzleGraph::Node::SQUARE_VERT_PADDING_PX);

		if(m_goalPathIterator != m_nodeList.end())
		{
			unsigned long currTime = m_clock.getElapsedTime().asMilliseconds();
			if(currTime - m_lastGoalFrameMillis > RENDERING_PAUSE_MILLIS)
			{
				--m_goalPathLength;
				m_goalPathNode = *m_goalPathIterator;
				++m_goalPathIterator;
				m_lastGoalFrameMillis = currTime;
			}
		}
	}
}
