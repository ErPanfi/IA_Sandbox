#ifndef ASTAR_SCENE_H
#define ASTAR_SCENE_H

#include <list>
#include "IScene.h"
#include "AStar\AStar.h"
#include "MapNode.h"
#include "MapData.h"
class MapData;


class AStarScene : public IScene
{
public:
	//ctors, dtor and =
	AStarScene();
	AStarScene(const AStarScene& other);
	~AStarScene();
	AStarScene& operator=(const AStarScene& other);

	virtual void	OnIdle();
	virtual void	OnDraw(sf::RenderWindow&);

private:
	//assignment-safe common methods
	void initFromOther(const AStarScene& other);
	void unInit();


	//the map graph
	static const unsigned int GRAPH_ROWS = 9;
	static const unsigned int GRAPH_COLS = 9;
	static const unsigned int GRAPH_START_ROW = 0;
	static const unsigned int GRAPH_START_COL = 0;
	static const unsigned int GRAPH_GOAL_ROW = GRAPH_ROWS - 1;
	static const unsigned int GRAPH_GOAL_COL = GRAPH_COLS - 1;
	MapData*				m_mapData;

	//AStar object
	typedef AStar<MapNode, false>	AStarType;
	AStarType				m_aStar;
	//current node opened
	AStarType::Node*		m_currNode;
	AStarType::Node*		m_prevNode;
	//recently frontiered nodes
	AStarType::NodeList		m_frontieredNodes;

	//drawing section
	struct RectangleDescriptor
	{
		float xOffset;
		float yOffset;
		float width;
		float height;
		sf::Color fillColor;
	};

	RectangleDescriptor* m_backgroundDescriptor;
	RectangleDescriptor* buildBackgroundDescriptor(unsigned int rows, unsigned int cols, bool transitability[], unsigned int rowGoal, unsigned int colGoal);
	inline void drawRect(RectangleDescriptor &rectDesc, sf::RenderWindow &renderWindow);
	
	void drawBackground(RectangleDescriptor *background, sf::RenderWindow& renderWindows);

	//AStar drawing section
	static const unsigned int SQUARE_HORIZ_PADDING_PX = 10;
	static const unsigned int SQUARE_WIDTH_PX = 50;
	static const unsigned int SQUARE_VERT_PADDING_PX = 10;
	static const unsigned int SQUARE_HEIGHT_PX = 50;

	void drawNode(AStarType::Node &targetNode, sf::RenderWindow& renderWindows);
	void buildAndDrawRectFromNode(MapNode &targetNode, const sf::Color &fillColor, sf::RenderWindow& renderWindows);

	//timer section
	static const unsigned long STEP_PAUSE_MILLIS = 1000;
	unsigned long m_lastStepMillis;
	sf::Clock m_stepClock;

	//flags management
	typedef unsigned char AStarSceneBitmask;
	AStarSceneBitmask m_flags;
	static const AStarSceneBitmask EMPTY_BITMASK = 0;
	
	//run started
	static const AStarSceneBitmask PERFORM_NEXT_STEP_BITMASK = 1;
	inline bool performNextStep() const { return (m_flags & PERFORM_NEXT_STEP_BITMASK) != EMPTY_BITMASK; }
	inline void setPerformNextStep(bool newValue)
	{
		if(newValue)
			m_flags |= PERFORM_NEXT_STEP_BITMASK;
		else
			m_flags &= ~PERFORM_NEXT_STEP_BITMASK;
	}

	//run started
	static const AStarSceneBitmask RUN_STARTED_BITMASK = PERFORM_NEXT_STEP_BITMASK << 1;
	inline bool runStarted() const { return (m_flags & RUN_STARTED_BITMASK) != EMPTY_BITMASK; }
	inline void setRunStarted(bool newValue)
	{
		if(newValue)
			m_flags |= RUN_STARTED_BITMASK;
		else
			m_flags &= ~RUN_STARTED_BITMASK;
	}

	//run finished
	static const AStarSceneBitmask RUN_FINISHED_BITMASK = RUN_STARTED_BITMASK << 1;
	inline bool runFinished() const { return (m_flags & RUN_FINISHED_BITMASK) != EMPTY_BITMASK; }
	inline void setRunFinished(bool newValue)
	{
		if(newValue)
			m_flags |= RUN_FINISHED_BITMASK;
		else
			m_flags &= ~RUN_FINISHED_BITMASK;
	}

	//goal found
	static const AStarSceneBitmask GOAL_FOUND_BITMASK = RUN_FINISHED_BITMASK << 1;
	inline bool goalFound() const { return (m_flags & GOAL_FOUND_BITMASK) != EMPTY_BITMASK; }
	inline void setGoalFound(bool newValue)
	{
		if(newValue)
			m_flags |= GOAL_FOUND_BITMASK;
		else
			m_flags &= ~GOAL_FOUND_BITMASK;
	}

	//goal drawed
	static const AStarSceneBitmask GOAL_DRAWED_BITMASK = GOAL_FOUND_BITMASK  << 1;
	inline bool goalDrawed() const { return (m_flags & GOAL_DRAWED_BITMASK) != EMPTY_BITMASK; }
	inline void setGoalDrawed(bool newValue)
	{
		if(newValue)
			m_flags |= GOAL_DRAWED_BITMASK;
		else
			m_flags &= ~GOAL_DRAWED_BITMASK;
	}

	//debug methods
	void echoNodes(AStarType::Node &node) const;
	void echoNodes(AStarType::NodeList &nodeList) const;
};

#endif