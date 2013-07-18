#ifndef NULL
#define NULL = 0x0
#endif

#ifndef ASTARNODE_H
#define ASTARNODE_H

#include <list>

class AStarNode
{
private:
	//node coords
	int row;
	int col;

	//flags byte
	unsigned char nodeFlags;

	void setTransitable(bool newValue)
	{
		if(newValue)
		{
			nodeFlags = nodeFlags | BITMASK_ISTRANSITABLE;
		}
		else
		{
			nodeFlags = nodeFlags & ~BITMASK_ISTRANSITABLE;
		}
	}


public:
	//constructor
	AStarNode(int rowValue, int colValue, bool isTransitable)
	{
		row = rowValue;
		col = colValue;
		GValue = 0;
		HValue = 0;
		nodeFlags = isTransitable ? BITMASK_ISTRANSITABLE : 0;
		parent = NULL;
	}

	//getter of private attributes
	int getRow() const { return row; }
	int getCol() const { return col; }

	//I admit: this is a teacher idea, but I like it =]
	bool operator==(const AStarNode &equals) const
	{
		return getRow() == (equals.getRow()) && getCol() == (equals.getCol());
	}
	bool operator!=(const AStarNode &different) const
	{
		return getRow() != (different.getRow()) && getCol() != (different.getCol());
	}

	//open flag mask & methods
	static const unsigned char BITMASK_ISOPEN = 1;
	bool isOpen()
	{
		return (nodeFlags & BITMASK_ISOPEN) != 0;
	}
	void setOpen(bool newValue)
	{
		if(newValue)
		{
			nodeFlags = nodeFlags | BITMASK_ISOPEN;
		}
		else
		{
			nodeFlags = nodeFlags & ~BITMASK_ISOPEN;
		}
	}

	//visited flag mask & methods
	static const unsigned char	BITMASK_ISVISITED = (BITMASK_ISOPEN << 1);
	bool isVisited()
	{
		return (nodeFlags & BITMASK_ISVISITED) != 0;
	}
	void setVisited(bool newValue)
	{
		if(newValue)
		{
			nodeFlags = nodeFlags | BITMASK_ISVISITED;
		}
		else
		{
			nodeFlags = nodeFlags & ~BITMASK_ISVISITED;
		}
	}

	//transitable flag mask & methods
	static const unsigned char BITMASK_ISTRANSITABLE = (BITMASK_ISVISITED << 1);
	bool isTransitable()
	{
		return (nodeFlags & BITMASK_ISTRANSITABLE) != 0;
	}

	//parent node for path storage
	AStarNode* parent;
	//A* values
	int HValue;
	int GValue;
	//adjacent nodes
	std::list<AStarNode*> adjacentNodes;
};

#endif	//NODE_H