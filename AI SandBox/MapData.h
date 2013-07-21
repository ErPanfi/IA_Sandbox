#ifndef ASTAR_MAPDATA_H
#define ASTAR_MAPDATA_H

#include "MapNode.h"

class MapData
{
	/*
public:
	unsigned int maxRows;
	unsigned int maxCols;
	*/

private:
	MapNode** m_map;
	unsigned int m_maxRows;
	unsigned int m_maxCols;
	unsigned int m_goalRow;
	unsigned int m_goalCol;
	unsigned int m_startRow;
	unsigned int m_startCol;

	void initFromOther(const MapData& other);
	void unInit();

	//rapid indexing function
	inline unsigned int idx(unsigned int row, unsigned int col) const { return row * m_maxCols + col; }
	//Node self-destruction handling
	friend MapNode::~MapNode();

public:
	//ctors, dtor and assignment
	MapData(unsigned int rows, unsigned int cols, bool transitability[], unsigned int startRow, unsigned int startCol, unsigned int goalRow, unsigned int goalCol);
	~MapData();
	MapData(const MapData& other);
	MapData& operator=(const MapData& other);


	//attributes getters
	inline unsigned int getNRows()		const { return m_maxRows; }
	inline unsigned int getNCols()		const { return m_maxCols; }
	inline unsigned int getGoalCol()	const { return m_goalCol; }
	inline unsigned int getGoalRow()	const { return m_goalRow; }
	inline unsigned int getStartCol()	const { return m_startCol; }
	inline unsigned int getStartRow()	const { return m_startRow; }

	//get the node state, invalid if node doesn't exists
	//inline MapNode::CellStateEnum getCellState(unsigned int row, unsigned int col) const { return (row < m_maxRows && col < m_maxCols) ? m_map[row * m_maxCols + col] -> getState() : MapNode::CellStateEnum::Invalid; }
	//obtain node reference, nullptr if doesn't exists
	inline MapNode* getNodePtr(unsigned int row, unsigned int col) const { return (row < m_maxRows && col < m_maxCols) ? m_map[row * m_maxCols + col] : nullptr; }
	//rapid references to start and end nodes
	inline MapNode& getStartNodeRef() const { return *m_map[idx(m_startRow,m_startCol)]; }
	inline MapNode& getGoalNodeRef() const { return *m_map[idx(m_goalRow,m_goalCol)]; }
	//building transitable neighbors list of a given node
	void buildNeighborsList(MapNode &start, std::list<MapNode*>& neighboursList);

};

#endif