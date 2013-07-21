#include "MapNode.h"

MapNode::MapNode(MapData &map, unsigned int row, unsigned int col, CellStateEnum state)
	: m_row(row)
	, m_col(col)
	, m_state(state)
	, m_map(&map)

{
}

void MapNode::buildNeighborsList(std::list<MapNode*>& neighboursList)
{
	m_map -> buildNeighborsList(*this, neighboursList);
}