#ifndef ASTAR_PUZZLENODE_H
#define ASTAR_PUZZLENODE_H

#include <sfml/Window.hpp>
#include <sfml/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "FontManager.h"

class PuzzleGraph;

template <unsigned int BOARD_EDGE_SIZE>
class PuzzleNode
{
public:
	static const unsigned int BOARD_SIZE = BOARD_EDGE_SIZE * BOARD_EDGE_SIZE;
	static const unsigned int EMPTY_SPACE = 99;

	struct CellCoords
	{
		unsigned int x;
		unsigned int y;

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
	};

private:

	unsigned int m_board[BOARD_SIZE];
	CellCoords m_emptySpaceCoords;

	PuzzleGraph* m_puzzleGraph;

	static inline unsigned int idx(unsigned int x, unsigned int y) { return x * BOARD_EDGE_SIZE + y; }

public:

	//some getters
	inline unsigned int getNumber(CellCoords &coords) const { return m_board[coords.idx()]; }
	inline CellCoords getEmptyCellCoords() const { return m_emptySpaceCoords; }

	PuzzleNode(unsigned int (&boardComposition)[BOARD_SIZE], PuzzleGraph* graph)
		: m_puzzleGraph(graph)
	{
		for(int i = 0; i < BOARD_SIZE; ++i)
		{
			m_board[i] = boardComposition[i];
			if(m_board[i] == EMPTY_SPACE)
				m_emptySpaceCoords = CellCoords(i);
		}
	}

	PuzzleNode()
		: m_puzzleGraph(nullptr)
	{
		for(int i = 0; i < BOARD_SIZE; ++i)
			m_board[i] = 0;
	}

	//drawing methods
	static const float SQUARE_HORIZ_PADDING_PX;
	static const float SQUARE_WIDTH_PX;
	static const float SQUARE_VERT_PADDING_PX;
	static const float SQUARE_HEIGHT_PX;
	static const float TEXT_HORIZ_PADDING_PX;
	static const float TEXT_VERT_PADDING_PX;

	void drawOnScreen(sf::RenderWindow& renderWin)
	{
		//draw background square
		sf::RectangleShape rectangle(sf::Vector2f(
													3.0f * SQUARE_HORIZ_PADDING_PX + BOARD_EDGE_SIZE* (SQUARE_HORIZ_PADDING_PX + SQUARE_WIDTH_PX),
													3.0f * SQUARE_VERT_PADDING_PX + BOARD_EDGE_SIZE * (SQUARE_HEIGHT_PX + SQUARE_VERT_PADDING_PX)
												 )
									);
		rectangle.setPosition(SQUARE_HORIZ_PADDING_PX, SQUARE_VERT_PADDING_PX);
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
										3.0f * SQUARE_VERT_PADDING_PX +  i * (SQUARE_HEIGHT_PX + SQUARE_VERT_PADDING_PX)
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
};

template <unsigned int BOARD_EDGE_SIZE>
const float PuzzleNode<BOARD_EDGE_SIZE>::SQUARE_HORIZ_PADDING_PX	= 15.0f;
template <unsigned int BOARD_EDGE_SIZE>
const float PuzzleNode<BOARD_EDGE_SIZE>::SQUARE_WIDTH_PX			= 75.0f;
template <unsigned int BOARD_EDGE_SIZE>
const float PuzzleNode<BOARD_EDGE_SIZE>::SQUARE_VERT_PADDING_PX		= 15.0f;
template <unsigned int BOARD_EDGE_SIZE>
const float PuzzleNode<BOARD_EDGE_SIZE>::SQUARE_HEIGHT_PX			= 75.0f;
template <unsigned int BOARD_EDGE_SIZE>
const float PuzzleNode<BOARD_EDGE_SIZE>::TEXT_HORIZ_PADDING_PX		= 8.0f;
template <unsigned int BOARD_EDGE_SIZE>
const float PuzzleNode<BOARD_EDGE_SIZE>::TEXT_VERT_PADDING_PX		= 8.0f;

#endif