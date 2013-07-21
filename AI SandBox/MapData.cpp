#include "MapNode.h"
#include "MapData.h"

MapData::MapData(unsigned int rows, unsigned int cols, bool transitability[], unsigned int startRow, unsigned int startCol, unsigned int goalRow, unsigned int goalCol)
	: m_maxRows(rows)
	, m_maxCols(cols)
	, m_goalRow(goalRow)
	, m_goalCol(goalCol)
	, m_startCol(startCol)
	, m_startRow(startRow)
{
	m_map = new MapNode*[rows * cols]();
	int l = 0;

	for(unsigned int i = 0 ; i < rows; ++i)
	{
		for(unsigned int j = 0; j < cols; ++j, ++l)
			m_map[l] = new MapNode(*this, i, j, transitability[l] ? MapNode::CellStateEnum::Free : MapNode::CellStateEnum::Blocked);
	}
}

void MapData::unInit()
{
	delete[] m_map;	//destroy all nodes
}

void MapData::initFromOther(const MapData& other)
{
	m_maxRows = other.m_maxRows;
	m_maxCols = other.m_maxCols;

	m_map = new MapNode*[m_maxRows + m_maxCols]();

	for(unsigned int i = 0; i < m_maxCols * m_maxRows; ++i)
		m_map[i] = new MapNode(*(other.m_map[i]));
}

MapData::~MapData()
{
	unInit();
}

MapData::MapData(const MapData& other)
{
	initFromOther(other);
}

MapData& MapData::operator=(const MapData& other)
{
	if(this != &other)
	{
		unInit();
		initFromOther(other);
	}

	return *this;
}

void MapData::buildNeighborsList(MapNode& start, std::list<MapNode*>& neighboursList)
{
	neighboursList.clear();

	/*
	int minRow = ((int)(start.getRow())) - 1;
	if(minRow < 0)
		minRow = 0;
	int maxRow = ((int)(start.getRow())) + 1;
	if(maxRow > m_maxRows)
		maxRow = m_maxRows;

	int minCol = ((int)(start.getCol())) - 1;
	if(minCol < 0)
		minCol = 0;
	int maxCol = ((int)(start.getCol())) + 1;
	if(maxCol > m_maxCols)
		maxCol = m_maxCols;
	*/
	//optimize cache
	int limits[] = 
	{
		std::max<int>((int)(start.getRow()) - 1, 0),					//min row
		std::min<int>((int)(start.getRow()) + 1, (int)(m_maxRows) - 1),	//max row
		std::max<int>((int)(start.getCol()) - 1, 0),					//min col	
		std::min<int>((int)(start.getCol()) + 1, (int)(m_maxCols) - 1)	//max col
	};

	for(int currRow = limits[0]; currRow <= limits[1]; ++currRow)
	{
		for(int currCol = limits[2]; currCol <= limits[3]; ++currCol)
		{
			if(
				(currRow != start.getRow() || currCol != start.getCol()) && 					//curr node is not the starting node (self-neighbouring not allowed)
				(m_map[idx(currRow, currCol)] -> getState() == MapNode::CellStateEnum::Free)	//node is transitable
			  )			
			{
				neighboursList.push_back(m_map[idx(currRow, currCol)]);
			}
		}
	}
}
