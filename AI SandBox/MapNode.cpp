#include "MapNode.h"
#include "MapData.h"

int MapNode::s_countNodes = 0;

MapNode::MapNode(MapData &map, unsigned int row, unsigned int col, CellStateEnum state)
	: m_row(row)
	, m_col(col)
	, m_state(state)
	, m_map(&map)

{
	++s_countNodes;
}

MapNode::MapNode()
	: m_row(0)
	, m_col(0)
	, m_state(CellStateEnum::Invalid)
	, m_map(nullptr)
{}

void MapNode::buildNeighborsList(std::list<MapNode*>& neighboursList)
{
	m_map -> buildNeighborsList(*this, neighboursList);
}

MapNode::~MapNode()
{
	--s_countNodes;
}

float MapNode::computeHValue()		//euclidean distance between points
{ 
	int rowDist = m_map -> getGoalRow() - m_row;
	int colDist = m_map -> getGoalCol() - m_col;
	return std::sqrtf((float)(rowDist*rowDist + colDist*colDist));
}

