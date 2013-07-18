#include "SteeringBehaviors.h"
#include "Agent.h"
#include <math.h>
#include <cassert>
#include "Application.h"

SteeringBehaviors::SteeringBehaviors(Agent* agent)
										: m_agent(agent),
											m_iFlags(0)						
{
}

SteeringBehaviors::~SteeringBehaviors()
{
}

void SteeringBehaviors::Calculate()
{
	m_steering.Zero();
	SumForces();

	m_steering.Truncate(m_agent->GetMaxSpeed());
}

void SteeringBehaviors::SumForces()
{
	Vector2 force = Vector2::ZERO;

	if (SeekIsOn())
	{
		force += Seek(m_target);
	}
	if (ArriveIsOn())
	{
		force += Arrive(m_target);
	}
	m_steering += force;
}

Vector2 SteeringBehaviors::Seek(const Vector2 &target)
{
	return Vector2::ZERO;
}

Vector2 SteeringBehaviors::Arrive(const Vector2& target)
{	
	return Vector2::ZERO;
}