#ifndef NULL
#define NULL = 0x0
#endif

#ifndef ASTARNODE_H
#define ASTARNODE_H

template <class T>
class AStarNode
{
public:
	typedef unsigned char NodeBitmask;
private:
	//node content
	T* m_state;

	//flags byte
	NodeBitmask m_nodeFlags;

	//parent node for path storage
	AStarNode<T>* m_parent;
	//A* values
	float m_HValue;
	float m_GValue;

	/*
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
	*/


public:

	static const NodeBitmask BITMASK_EMPTY = 0;

	//constructor
	AStarNode(T& nodeContent, AStarNode* parent, float nodeHValue)
	{
		/*
		row = rowValue;
		col = colValue;
		nodeFlags = isTransitable ? BITMASK_ISTRANSITABLE : 0;
		*/

		m_GValue = (m_parent = parent) ? m_parent -> m_GValue + 1 : 0;
		m_HValue = nodeHValue;
		nodeFlags = BITMASK_EMPTY;
		m_state = &nodeContent;
	}

	//getter of private attributes

	T getState() const { return state; }
	
	inline float getHValue() const { return m_HValue; }
	
	inline float getGValue() const { return m_GValue; }
	inline void setGValue(float newValue)
	{
		m_GValue = newValue;
	}

	inline AStarNode* getParent() const { return m_parent; }
	inline void setParent(AStarNode* newValue)
	{
		m_parent = newValue;
	}

	/*
	int getRow() const { return row; }
	int getCol() const { return col; }
	*/

	//I admit: this is a teacher idea, but I like it =]
	bool operator==(const AStarNode &equals) const
	{
		//return getRow() == (equals.getRow()) && getCol() == (equals.getCol());
		return m_state == equals.m_state;
	}
	bool operator!=(const AStarNode &different) const
	{
		//return getRow() != (different.getRow()) && getCol() != (different.getCol());
		return m_state != different.m_state;
	}
	
	bool operator<(const AStarNode &other)
	{
		return m_GValue + m_HValue < (other.m_GValue + other.m_HValue) || m_state < other.m_state;
	}


	//open flag mask & methods
	static const NodeBitmask BITMASK_ISOPEN = 1;
	bool isOpen()
	{
		return (m_nodeFlags & BITMASK_ISOPEN) != 0;
	}
	void setOpen(bool newValue)
	{
		if(newValue)
		{
			m_nodeFlags = m_nodeFlags | BITMASK_ISOPEN;
		}
		else
		{
			m_nodeFlags = m_nodeFlags & ~BITMASK_ISOPEN;
		}
	}

	//visited and transitable flag mask & methods
	/*
	static const Bitmask BITMASK_ISVISITED = (BITMASK_ISOPEN << 1);
	bool isVisited()
	{
		return (m_nodeFlags & BITMASK_ISVISITED) != 0;
	}
	void setVisited(bool newValue)
	{
		if(newValue)
		{
			m_nodeFlags = m_nodeFlags | BITMASK_ISVISITED;
		}
		else
		{
			m_nodeFlags = m_nodeFlags & ~BITMASK_ISVISITED;
		}
	}
 
	//transitable flag mask & methods

	static const unsigned char BITMASK_ISTRANSITABLE = (BITMASK_ISVISITED << 1);
	bool isTransitable()
	{
		return (nodeFlags & BITMASK_ISTRANSITABLE) != 0;
	}
	*/

};

#endif	//NODE_H