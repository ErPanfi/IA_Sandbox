#ifndef ASTAR_MAPNODE_H
#define ASTAR_MAPNODE_H

#include <list>
#include "MapData.h"

class MapNode
{
public:
	enum CellStateEnum
	{
		Invalid = -1,
		Free = 0,
		Blocked,
		COUNT
	};


private:

	CellStateEnum m_state;
	unsigned int  m_row;
	unsigned int  m_col;

	MapData* m_map;

	//ctor accessible only from the map containing the node
	friend MapData::MapData(unsigned int rows, unsigned int cols, bool transitability[], unsigned int startRow, unsigned int startCol, unsigned int goalRow, unsigned int goalCol);
	MapNode(MapData &map, unsigned int  row, unsigned int  col, CellStateEnum state);

public:

	//getters
	inline unsigned int getRow() const { return m_row; }
	inline unsigned int getCol() const { return m_col; }
	inline CellStateEnum getState() const { return m_state; }

	inline bool operator<(const MapNode& other) const
	{
		return	m_map < other.m_map || 
				(m_map == other.m_map && 
					(m_row < other.m_row) || 
					(m_row == other.m_row && m_col < other.m_col)
				);
	}

	bool operator==(const MapNode& other) const { return m_row == other.m_row && m_col == other.m_col; }
	bool operator!=(const MapNode& other) const { return !(*this == other); }

	inline float computeHValue()		//euclidean distance between points
	{ 
		int rowDist = m_map -> getGoalRow() - m_row;
		int colDist = m_map -> getGoalCol() - m_col;
		return std::sqrtf((float)(rowDist*rowDist + colDist*colDist));
	}

	void buildNeighborsList(std::list<MapNode*>& neighboursList);

};

#endif