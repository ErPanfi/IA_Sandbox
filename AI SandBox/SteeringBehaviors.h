#ifndef STEERINGBEHAVIORS_H
#define STEERINGBEHAVIORS_H

#include "Vector2.h"

class Agent;

class SteeringBehaviors
{

public:
	SteeringBehaviors(Agent* bp);
	~SteeringBehaviors();

	Vector2 GetTarget()const{ return m_target; }
	void SetTarget(const Vector2 target){ m_target = target; }
	
	Vector2 GetForce()const{ return m_steering; }

	void Calculate();

	inline void SeekOn(){ m_iFlags |= seek; }
	inline void ArriveOn(){ m_iFlags |= arrive; }

	inline void SeekOff(){ if(SeekIsOn()) m_iFlags ^= seek; }
	inline void ArriveOff(){ if(ArriveIsOn()) m_iFlags ^= arrive; }

	inline bool SeekIsOn(){ return On(seek); }
	inline bool ArriveIsOn(){ return On(arrive); }

private:
	
	Agent*			m_agent;
	
	Vector2			m_steering;
	Vector2			m_target;

	int				m_iFlags;

	enum Behaviors
	{
		none               = 0x0000,
		seek               = 0x0001,
		arrive             = 0x0002
	};

	bool	On(Behaviors bt){return ((m_iFlags & bt) == bt);}

	void SumForces();

	Vector2 Seek(const Vector2& target);
	Vector2 Arrive(const Vector2& target);

};

#endif