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

	static int s_countNodes;

private:
	//node content
	T* m_content;

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
	AStarNode(T& nodeContent, AStarNode* parent, float hValue)
	{
		/*
		row = rowValue;
		col = colValue;
		nodeFlags = isTransitable ? BITMASK_ISTRANSITABLE : 0;
		*/

		m_content = &nodeContent;
		m_GValue = (m_parent = parent) ? m_parent -> m_GValue + 1 : 0;
		m_HValue = hValue;
		m_nodeFlags = BITMASK_EMPTY;

		++s_countNodes;
	}

	~AStarNode() { --s_countNodes; }

	//getter of private attributes

	T& getContent() const { return *m_content; }
	
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
	inline bool operator==(const AStarNode &equals) const
	{
		return *m_content == *equals.m_content;
	}
	inline bool operator!=(const AStarNode &different) const
	{
		return !(*this == different);
	}

	inline bool operator<(const AStarNode &other) const
	{
		return (
					!(*m_content == *other.m_content) &&			//conditio sine qua non is that contents have to be different
					(
						totalDistance() < (other.totalDistance()) ||								//total distance is lesser
						(totalDistance() == (other.totalDistance()) && *m_content < *other.m_content)	//or, if distance is equal, content is lesser
					)
				);
	}

	inline float totalDistance() const { return m_GValue + m_HValue; }

	//flags management

	//open flag mask & methods
	static const NodeBitmask BITMASK_ISOPEN = 1;
	inline bool isOpen()
	{
		return (m_nodeFlags & BITMASK_ISOPEN) != BITMASK_EMPTY;
	}
	inline void setOpen(bool newValue)
	{
		if(newValue)
		{
			m_nodeFlags |= BITMASK_ISOPEN;
		}
		else
		{
			m_nodeFlags &= ~BITMASK_ISOPEN;
		}
	}

	//frontiered flag mask & methods

	static const NodeBitmask BITMASK_ISFRONTIERED = (BITMASK_ISOPEN << 1);
	inline bool isFrontiered()
	{
		return (m_nodeFlags & BITMASK_ISFRONTIERED) != BITMASK_EMPTY;
	}
	inline void setFrontiered(bool newValue)
	{
		if(newValue)
		{
			m_nodeFlags |= BITMASK_ISFRONTIERED;
		}
		else
		{
			m_nodeFlags &= ~BITMASK_ISFRONTIERED;
		}
	}
 
	//goalPath flag mask & methods
	

	static const NodeBitmask BITMASK_ISINGOALPATH = (BITMASK_ISFRONTIERED << 1);
	inline bool isInGoalPath()
	{
		return (m_nodeFlags & BITMASK_ISINGOALPATH) != BITMASK_EMPTY;
	}
	inline void setInGoalPath(bool newValue)
	{
		if(newValue)
		{
			m_nodeFlags |= BITMASK_ISINGOALPATH;
		}
		else
		{
			m_nodeFlags &= BITMASK_ISINGOALPATH;
		}
	}
};

template <class T>
int AStarNode<T>::s_countNodes = 0;

#endif	//NODE_H