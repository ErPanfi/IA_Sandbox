#ifndef ASTAR_MAPNODE_H
#define ASTAR_MAPNODE_H

#include <list>
class MapData;

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

	//check for memory leaks
	static int s_countNodes;


private:

	CellStateEnum m_state;
	unsigned int  m_row;
	unsigned int  m_col;

	MapData* m_map;

public:

	MapNode(MapData &map, unsigned int  row, unsigned int  col, CellStateEnum state);
	MapNode();
	~MapNode();
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

	float computeHValue();		//euclidean distance between points

	void buildNeighborsList(std::list<MapNode*>& neighboursList);

};

#endif