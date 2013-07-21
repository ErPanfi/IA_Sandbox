#include <iostream>
#include "AStarScene.h"

void AStarScene::initFromOther(const AStarScene& other)
{
	m_mapData = new MapData(*other.m_mapData);
	m_aStar = AStarType(other.m_aStar);
	m_currNode = new AStarType::Node(*other.m_currNode);
	m_frontieredNodes = AStarType::NodeList(other.m_frontieredNodes);
	m_backgroundDescriptor = new RectangleDescriptor[GRAPH_COLS * GRAPH_ROWS + 1];
	for(int i = 0; i < GRAPH_COLS * GRAPH_ROWS + 1; ++i)
		m_backgroundDescriptor[i] = other.m_backgroundDescriptor[i];
}

void AStarScene::unInit()
{
	delete m_currNode;
	delete m_mapData;
	delete[] m_backgroundDescriptor;
}

AStarScene::AStarScene(const AStarScene& other)
{
	initFromOther(other);
}

AStarScene::AStarScene()
{

	bool transitability[] = {
		true,	true,	true,	false,	true,	true,	true,	true,	true,	
		true,	false,	true,	false,	true,	false,	true,	false,	true,
		true,	false,	true,	false,	true,	false,	true,	false,	true,
		true,	false,	true,	false,	true,	false,	true,	false,	true,
		true,	false,	true,	false,	true,	false,	true,	false,	true,
		true,	false,	true,	false,	true,	false,	true,	false,	true,
		true,	false,	true,	true,	true,	false,	true,	false,	true,
		true,	false,	false,	false,	false,	false,	false,	false,	true,
		true,	true,	true,	true,	true,	true,	true,	false,	true,	

	};
	
	m_mapData = new MapData(GRAPH_ROWS, GRAPH_COLS, transitability,GRAPH_START_ROW, GRAPH_START_COL, GRAPH_GOAL_ROW, GRAPH_GOAL_COL);
	m_backgroundDescriptor = buildBackgroundDescriptor(GRAPH_ROWS, GRAPH_COLS, transitability, GRAPH_GOAL_ROW, GRAPH_GOAL_COL);
	m_currNode = new AStarType::Node(m_mapData -> getStartNodeRef(), nullptr, m_mapData -> getStartNodeRef().computeHValue());
	m_flags = EMPTY_BITMASK;
	m_stepClock.restart();
	m_lastStepMillis = 0;
}

AStarScene::~AStarScene()
{
	unInit();
}

AStarScene& AStarScene::operator=(const AStarScene& other)
{
	if(this != &other)
	{
		unInit();
		initFromOther(other);
	}

	return *this;
}

void AStarScene::OnIdle()
{
	if(!runFinished() && m_stepClock.getElapsedTime().asMilliseconds() - m_lastStepMillis >= STEP_PAUSE_MILLIS)
	{
		std::cout << "Performing AStar step." << std::endl;
		m_lastStepMillis = m_stepClock.getElapsedTime().asMilliseconds();
		if(!m_currNode)
		{
			std::cout << "Path not found" << std::endl;
			setRunFinished(true);
		}
		else if(m_currNode -> getContent() == m_mapData -> getGoalNodeRef())
		{
			AStarType::Node* backtrack = m_currNode;	//mantain m_currNode reference, in order to draw goal and avoid memory leaks
			setRunFinished(true);
			setGoalFound(true);
			m_frontieredNodes.clear();
			while(backtrack)
			{
				backtrack -> setInGoalPath(true);
				m_frontieredNodes.push_front(backtrack);
				backtrack = backtrack -> getParent();
			}
			std::cout << "Goal found! Here is the path." << std::endl;
			echoNodes(m_frontieredNodes);
		}
		else
		{
			std::cout << "Exploring this node." << std::endl;
			echoNodes(*m_currNode);
			m_frontieredNodes.clear();		//I'm afraid this isn't needed anymore
			m_aStar.openNode(m_currNode, m_frontieredNodes);

			std::cout << "Frontiered these nodes" << std::endl;
			echoNodes(m_frontieredNodes);

			m_prevNode = m_currNode;
			m_currNode = m_aStar.decideNextNodeToExplore();
		}
	}
}

void AStarScene::OnDraw(sf::RenderWindow& renderWindow)
{
	//first draw background
	drawBackground(m_backgroundDescriptor, renderWindow);
	
	//then draw open nodes
	AStarType::NodeSet::iterator iter;
	AStarType::NodeSet::iterator endIter;

	m_aStar.getOpenNodesIterators(iter, endIter);
	for(; iter != endIter; ++iter)
		drawNode(**iter, renderWindow);

	//and then frontier nodes
	m_aStar.getFrontierNodesIterators(iter, endIter);
	for(; iter != endIter; ++iter)
		drawNode(**iter, renderWindow);

	//and, finally, the missing node
	if(m_currNode)	//if A* is still exploring the solution space draw next node to explore
		drawNode(*m_currNode, renderWindow);
}

AStarScene::RectangleDescriptor* AStarScene::buildBackgroundDescriptor(unsigned int rows, unsigned int cols, bool transitability[], unsigned int rowGoal, unsigned int colGoal)
{
	RectangleDescriptor* ret = new RectangleDescriptor[rows * cols + 1];	//this stores the background square as first element
	int x = 0;

	sf::Color transitableColor = sf::Color::White;
	transitableColor.a = 255 * 7 / 10;

	sf::Color untransitableColor = sf::Color::Red;
	untransitableColor.a = 255 * 7 / 10;
	
	sf::Color goalColor = sf::Color::Green;
	goalColor.a = 255 * 7 / 10;
	
	//build background black square
	ret[x].width = 3.0f * SQUARE_HORIZ_PADDING_PX + GRAPH_COLS* (SQUARE_HORIZ_PADDING_PX + SQUARE_WIDTH_PX);
	ret[x].height = 3.0f * SQUARE_VERT_PADDING_PX + GRAPH_ROWS * (SQUARE_HEIGHT_PX + SQUARE_VERT_PADDING_PX);
	ret[x].xOffset = (float)SQUARE_HORIZ_PADDING_PX;
	ret[x].yOffset = (float)SQUARE_VERT_PADDING_PX;
	ret[x].fillColor = sf::Color::Black;

	//build a square for every transitability value
	for(unsigned int row = 0; row < rows; ++row)
	{
		for(unsigned int col = 0; col < cols; ++col)
		{
			ret[++x].width = (float)SQUARE_WIDTH_PX;
			ret[x].height = (float)SQUARE_HEIGHT_PX;
			ret[x].xOffset = 3.0f * SQUARE_HORIZ_PADDING_PX + (col * (SQUARE_HORIZ_PADDING_PX + SQUARE_WIDTH_PX));
			ret[x].yOffset = 3.0f * SQUARE_VERT_PADDING_PX + (row * (SQUARE_VERT_PADDING_PX + SQUARE_HEIGHT_PX));
			ret[x].fillColor = (row == rowGoal && col == colGoal) ? goalColor : ( transitability[x-1] ? transitableColor : untransitableColor);
		}
	}

	//return the descriptor array
	return ret;
}

inline void AStarScene::drawRect(RectangleDescriptor &rectDesc, sf::RenderWindow &renderWindow)
{
	sf::RectangleShape nodeRect(sf::Vector2f(rectDesc.width, rectDesc.height));
	nodeRect.setPosition(rectDesc.xOffset, rectDesc.yOffset);
	nodeRect.setFillColor(rectDesc.fillColor);
	renderWindow.draw(nodeRect);
}


void AStarScene::drawBackground(RectangleDescriptor *backgroundDesc, sf::RenderWindow& renderWindow)
{
	for(unsigned int i = 0; i <= GRAPH_ROWS * GRAPH_COLS; ++i)
	{
		drawRect(backgroundDesc[i], renderWindow);
	}
}

void AStarScene::drawNode(AStarType::Node &targetNode, sf::RenderWindow& renderWindow)
{
	MapNode* mapNode = &(targetNode.getContent());
	if(targetNode.isInGoalPath())
		buildAndDrawRectFromNode(*mapNode, sf::Color::Green, renderWindow); //std::cout << "Node in (" << mapNode -> getRow() << ", " << mapNode -> getCol() << ") is in goal path." << std::endl;
	else if(&targetNode == m_currNode)
		buildAndDrawRectFromNode(*mapNode, sf::Color::Yellow, renderWindow);
	else if(mapNode -> getState() == MapNode::CellStateEnum::Blocked)
		buildAndDrawRectFromNode(*mapNode, sf::Color::Red, renderWindow); //std::cout << "Node in (" << mapNode -> getRow() << ", " << mapNode -> getCol() << ") is blocked." << std::endl;
	else if(targetNode.isFrontiered())
		buildAndDrawRectFromNode(*mapNode, sf::Color::Cyan, renderWindow); //std::cout << "Node in (" << mapNode -> getRow() << ", " << mapNode -> getCol() << ") is frontiered." << std::endl;
	else if(targetNode.isOpen())
		buildAndDrawRectFromNode(*mapNode, sf::Color::Blue, renderWindow); //std::cout << "Node in (" << mapNode -> getRow() << ", " << mapNode -> getCol() << ") is open." << std::endl;
	else	//should never happen
		buildAndDrawRectFromNode(*mapNode, sf::Color::White, renderWindow); //std::cout << "Node in (" << mapNode -> getRow() << ", " << mapNode -> getCol() << ") is unexplored." << std::endl;
}

void AStarScene::buildAndDrawRectFromNode(MapNode &targetNode, const sf::Color &fillColor, sf::RenderWindow& renderWindow)
{
	//Build a descriptor, instead
	/*
	sf::RectangleShape nodeRect(sf::Vector2f(
											(float)SQUARE_WIDTH_PX,
											(float)SQUARE_HEIGHT_PX
											)
								);
	nodeRect.setPosition(
							(float)2 * SQUARE_HORIZ_PADDING_PX + targetNode.getCol() * (SQUARE_HORIZ_PADDING_PX + SQUARE_WIDTH_PX),
							(float)2 * SQUARE_VERT_PADDING_PX + targetNode.getRow() * (SQUARE_VERT_PADDING_PX + SQUARE_HEIGHT_PX)
						);

	nodeRect.setFillColor(fillColor);

	renderWindows.draw(nodeRect);
	*/
	RectangleDescriptor rectDesc;
	rectDesc.width = (float)SQUARE_WIDTH_PX;
	rectDesc.height = (float)SQUARE_HEIGHT_PX;
	rectDesc.xOffset = 2.75f * SQUARE_HORIZ_PADDING_PX + targetNode.getCol() * (SQUARE_HORIZ_PADDING_PX + SQUARE_WIDTH_PX);
	rectDesc.yOffset = 2.75f * SQUARE_VERT_PADDING_PX + targetNode.getRow() * (SQUARE_VERT_PADDING_PX + SQUARE_HEIGHT_PX);
	rectDesc.fillColor = fillColor;

	drawRect(rectDesc, renderWindow);
}

//debug methods
void AStarScene::echoNodes(AStarType::NodeList &nodeList) const
{
	for(AStarType::NodeList::iterator iter = nodeList.begin(); iter != nodeList.end(); ++iter)
		echoNodes(**iter);
}

void AStarScene::echoNodes(AStarType::Node &node) const
{
	std::cout << "Node @ (" << node.getContent().getRow() << ", " << node.getContent().getCol() << ") , G = " << node.getGValue() << ", H  = " << node.getHValue() << std::endl;
}
