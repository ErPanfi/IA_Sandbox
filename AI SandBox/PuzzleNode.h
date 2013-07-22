#ifndef ASTAR_PUZZLENODE_H
#define ASTAR_PUZZLENODE_H

#include <sfml/Window.hpp>
#include <sfml/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <list>
#include "FontManager.h"

class PuzzleGraph;

template <unsigned int BOARD_EDGE_SIZE>
class PuzzleNode
{
public:
	static const unsigned int BOARD_SIZE = BOARD_EDGE_SIZE * BOARD_EDGE_SIZE;
	static const unsigned int EMPTY_SPACE = 99;

	static unsigned int s_nodeCount;

	class CellCoords
	{
	private:
		unsigned int x;
		unsigned int y;

	public:
		CellCoords(unsigned int _x, unsigned int _y)
			: x(_x)
			, y(_y)
		{}

		CellCoords()
			: x(0)
			, y(0)
		{}

		CellCoords(unsigned int boardIdx)
			: x(boardIdx / BOARD_EDGE_SIZE)
			, y(boardIdx % BOARD_EDGE_SIZE)
		{}

		inline unsigned int idx() const { return PuzzleNode::idx(x,y); }

		inline unsigned int manhattanDistanceTo(const CellCoords& other) {return std::abs((int)(x - other.x)) + std::abs((int)(y - other.y));}

		inline unsigned int getX() const { return x; }

		inline unsigned int getY() const { return y; }
	};

	enum MovementDirection
	{
		INVALID = -1,
		LEFT = 0,
		RIGHT,
		UP,
		DOWN,

		COUNT
	};

private:

	unsigned int m_board[BOARD_SIZE];
	CellCoords m_emptySpaceCoords;

	PuzzleGraph* m_puzzleGraph;

	float m_totalManhattanDistance;

	static inline unsigned int idx(unsigned int x, unsigned int y) { return x * BOARD_EDGE_SIZE + y; }

	PuzzleNode* buildNeighbour(MovementDirection direction)
	{
		int newX = m_emptySpaceCoords.getX();
		int newY = m_emptySpaceCoords.getY();

		switch (direction)
		{
		case LEFT:
			if(newX > 0)
				--newX;
			else
				return nullptr;
			break;
		case RIGHT:
			if(newX < BOARD_EDGE_SIZE - 1)
				++newX;
			else
				return nullptr;
			break;
		case UP:
			if(newY > 0)
				--newY;
			else
				return nullptr;
			break;
		case DOWN:
			if(newY < BOARD_EDGE_SIZE - 1)
				++newY;
			else
				return nullptr;
			break;

		default:
			return nullptr;
		}

		//if passed switch of death then neighbour exists!
		PuzzleNode *ret = new PuzzleNode(*this);	//copy this
		//swap empty cell with new idx
		unsigned int newIdx = PuzzleNode::idx(newX, newY);
		ret -> m_board[ret -> m_emptySpaceCoords.idx()] = ret -> m_board[newIdx];
		ret -> m_board[newIdx] = EMPTY_SPACE;
		ret -> m_emptySpaceCoords = CellCoords(newX, newY);
		//recalculate manhattan distance
		ret -> m_totalManhattanDistance = -1;
		ret -> computeHValue();

		//return new neighbour
		return ret;
	}

public:

	//some getters
	inline unsigned int getNumber(CellCoords &coords) const { return m_board[coords.idx()]; }
	inline CellCoords getEmptyCellCoords() const { return m_emptySpaceCoords; }

	PuzzleNode(unsigned int (&boardComposition)[BOARD_SIZE], PuzzleGraph* graph)
		: m_puzzleGraph(graph)
		, m_totalManhattanDistance(-1)
	{
		for(int i = 0; i < BOARD_SIZE; ++i)
		{
			m_board[i] = boardComposition[i];
			if(m_board[i] == EMPTY_SPACE)
				m_emptySpaceCoords = CellCoords(i);
		}

		computeHValue();

		++s_nodeCount;
	}

	PuzzleNode()
		: m_puzzleGraph(nullptr)
		, m_totalManhattanDistance(-1)
	{
		for(int i = 0; i < BOARD_SIZE; ++i)
			m_board[i] = 0;
	}

	~PuzzleNode()
	{
		--s_nodeCount;
	}

	//drawing methods
	static const float SQUARE_HORIZ_PADDING_PX;
	static const float SQUARE_WIDTH_PX;
	static const float SQUARE_VERT_PADDING_PX;
	static const float SQUARE_HEIGHT_PX;
	static const float TEXT_HORIZ_PADDING_PX;
	static const float TEXT_VERT_PADDING_PX;

	void drawOnScreen(sf::RenderWindow& renderWin, float yExtraOffset)
	{
		//draw background square
		sf::RectangleShape rectangle(sf::Vector2f(
													3.0f * SQUARE_HORIZ_PADDING_PX + BOARD_EDGE_SIZE* (SQUARE_HORIZ_PADDING_PX + SQUARE_WIDTH_PX),
													3.0f * SQUARE_VERT_PADDING_PX + BOARD_EDGE_SIZE * (SQUARE_HEIGHT_PX + SQUARE_VERT_PADDING_PX)
												 )
									);
		rectangle.setPosition(SQUARE_HORIZ_PADDING_PX, SQUARE_VERT_PADDING_PX + yExtraOffset);
		rectangle.setFillColor(sf::Color::Black);

		renderWin.draw(rectangle);

		//draw number cells
		const sf::Font *numbersFont = FontManager::Istance() -> GetFont(FontEnum::Font_Cyber);
		for(unsigned int i = 0; i < BOARD_EDGE_SIZE; ++i)
		{
			for(unsigned int j = 0; j < BOARD_EDGE_SIZE; ++j)
			{
				rectangle = sf::RectangleShape(sf::Vector2f(	SQUARE_WIDTH_PX,
																SQUARE_HEIGHT_PX
															 )
												);
				rectangle.setPosition(	
										3.0f * SQUARE_HORIZ_PADDING_PX + j * (SQUARE_HORIZ_PADDING_PX + SQUARE_WIDTH_PX),
										3.0f * SQUARE_VERT_PADDING_PX +  i * (SQUARE_HEIGHT_PX + SQUARE_VERT_PADDING_PX) + yExtraOffset
									);

				rectangle.setFillColor(sf::Color::White);

				renderWin.draw(rectangle);

				unsigned int cellContent = m_board[idx(i,j)];
				if(cellContent != EMPTY_SPACE)
				{
					std::stringstream stringStream;
					stringStream << cellContent;
					std::string numStr(stringStream.str());
					sf::Text text(numStr, *numbersFont);
					text.setPosition(rectangle.getPosition().x + TEXT_HORIZ_PADDING_PX, rectangle.getPosition().y + TEXT_VERT_PADDING_PX);
					text.setColor(sf::Color::Black);
					renderWin.draw(text);
				}
			}
		}


	}

	void echoBoard()
	{
		std::cout << "Echoing the board" << std::endl;
		for(unsigned int i = 0; i < BOARD_EDGE_SIZE; ++i)
		{
			for(unsigned int j = 0; j < BOARD_EDGE_SIZE; ++j)
				if(m_board[idx(i,j)] != EMPTY_SPACE) 
					std::cout << m_board[idx(i,j)] << "\t";
				else
					std::cout << "*\t";

			std::cout << std::endl;
		}
	}

	bool operator==(const PuzzleNode& other) const
	{
		//must pertain to same graph
		if(m_puzzleGraph != other.m_puzzleGraph)
			return false;

		//must have equal boards
		for(unsigned int i = 0; i < BOARD_SIZE; ++i)
		{
			if(m_board[i] != other.m_board[i]) 
				return false;
		}

		return true;
	}

	bool operator!=(const PuzzleNode& other) const
	{
		return !(*this == other);
	}

	//AStar required methods
	float computeHValue()
	{
		if(m_puzzleGraph && m_totalManhattanDistance < 0)
		{
			m_totalManhattanDistance = 0;

			for(unsigned int i = 0; i < BOARD_SIZE; ++i)
			{
				m_totalManhattanDistance += CellCoords(i).manhattanDistanceTo(CellCoords(m_board[i] - 1));
			}
		}

		return m_totalManhattanDistance;
	}

	void buildNeighborsList(std::list<PuzzleNode*>& neighboursList)
	{
		//evaluate each case: up, down, left, right
		for(unsigned int i = MovementDirection::LEFT; i < MovementDirection::COUNT; ++i)
		{
			PuzzleNode* newNode = buildNeighbour((MovementDirection) i);
			if(newNode)
				neighboursList.push_back(newNode);
		}
	}

	bool operator<(const PuzzleNode& other)
	{
		if(m_puzzleGraph < other.m_puzzleGraph)
			return true;
		
		for(unsigned int i = 0; i < BOARD_SIZE; ++i)
		{
			if(m_board[i] < other.m_board[i])
				return true;
			else if(m_board[i] > other.m_board[i])
				return false;
		}

		//here they're equals. Thus return false.
		return false;
	}
};

template <unsigned int BOARD_EDGE_SIZE>
const float PuzzleNode<BOARD_EDGE_SIZE>::SQUARE_HORIZ_PADDING_PX	= 15.0f;
template <unsigned int BOARD_EDGE_SIZE>
const float PuzzleNode<BOARD_EDGE_SIZE>::SQUARE_WIDTH_PX			= 75.0f;
template <unsigned int BOARD_EDGE_SIZE>
const float PuzzleNode<BOARD_EDGE_SIZE>::TEXT_HORIZ_PADDING_PX		= 8.0f;
template <unsigned int BOARD_EDGE_SIZE>
const float PuzzleNode<BOARD_EDGE_SIZE>::SQUARE_VERT_PADDING_PX		= 15.0f;
template <unsigned int BOARD_EDGE_SIZE>
const float PuzzleNode<BOARD_EDGE_SIZE>::SQUARE_HEIGHT_PX			= 75.0f;
template <unsigned int BOARD_EDGE_SIZE>
const float PuzzleNode<BOARD_EDGE_SIZE>::TEXT_VERT_PADDING_PX		= 8.0f;

//node counter
template <unsigned int BOARD_EDGE_SIZE>
unsigned int PuzzleNode<BOARD_EDGE_SIZE>::s_nodeCount = 0;
#endif