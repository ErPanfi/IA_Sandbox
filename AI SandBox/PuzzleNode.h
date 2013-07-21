#ifndef ASTAR_PUZZLENODE_H
#define ASTAR_PUZZLENODE_H

#include <sfml/Window.hpp>
#include <sfml/Graphics.hpp>

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

		inline unsigned int idx() const { return idx(x,y); }
	};

private:

	unsigned int m_board[BOARD_SIZE];
	CellCoords m_emptySpaceCoords,

	inline unsigned int idx(unsigned int x, unsigned int y) const { return x * BOARD_EDGE_SIZE + y; }

public:

	inline unsigned int getNumber(CellCoords &coords) const { return m_board[coords.idx()]; }

	PuzzleNode(unsigned int (&boardComposition)[BOARD_SIZE])
	{
		for(int i = 0; i < BOARD_SIZE; ++i)
		{
			m_board[i] = boardComposition[i];
			if(m_board[i] == EMPTY_SPACE)
				m_emptySpaceCoords = CellCoords(i / BOARD_EDGE_SIZE, i % BOARD_EDGE_SIZE);
		}
	}

	//drawing methods
	static const unsigned float SQUARE_HORIZ_PADDING_PX	= 10;
	static const unsigned float SQUARE_WIDTH_PX			= 50;
	static const unsigned float SQUARE_VERT_PADDING_PX	= 10;
	static const unsigned float SQUARE_HEIGHT_PX		= 50;

	void drawOnScreen()
	{
		sf::RectangleShape rectangle(sf::Vector2f(
													3.0f * SQUARE_HORIZ_PADDING_PX + GRAPH_COLS* (SQUARE_HORIZ_PADDING_PX + SQUARE_WIDTH_PX),
													3.0f * SQUARE_VERT_PADDING_PX + GRAPH_ROWS * (SQUARE_HEIGHT_PX + SQUARE_VERT_PADDING_PX)
												 )
									);
		rectangle.setPosition(SQUARE_HORIZ_PADDING_PX, SQUARE_VERT_PADDING_PX);
		rectangle.setFillColor(sf::Color::Black);

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

				unsigned int cellContent = m_board[idx(i,j)];
				if(cellContent != EMPTY_SPACE)
				{
					//TODO write number in rectangle
				}
			}
		}
	}
};

#endif