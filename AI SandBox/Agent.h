#ifndef AGENT_H
#define AGENT_H

#include "Vector2.h"
#include "StateMachine.h"
#include <sfml/Window.hpp>
#include <sfml/Graphics.hpp>

class SteeringBehaviors;

class Agent
{
public:

	Agent();

	Agent(float maxSpeed, Vector2 pos, Vector2 facing, Vector2 speed = Vector2::ZERO);

	virtual ~Agent();

	//GETTERS
	virtual inline std::string GetName()const{ return m_Name;}
	Vector2 GetPosition()const{ return m_pos; } 
	Vector2	GetSpeed()const{ return m_speed; }
	float GetMaxSpeed()const{ return m_maxSpeed; }
	Vector2 GetFacing()const{return m_facing; }

	//SETTERS
	virtual inline void SetPosition(const float x, const float y) { m_pos.x = x; m_pos.y = y; }
	virtual inline void	SetPosition(const Vector2& pos) { m_pos = pos; }

	virtual void Update();
	virtual void OnDraw(sf::RenderWindow&);

	int ID()const{	return m_ID;	}

protected:

	StateMachine<Agent>*	m_FSM;
	SteeringBehaviors*		m_steer;

	//unique id for each entity
	int m_ID;

	std::string m_Name;

	Vector2	m_pos;
	Vector2 m_speed;
	float m_maxSpeed;
	Vector2 m_facing;

	sf::Color m_AgentColor;

	//next valid ID. When an Agent is istantiated the value is updated.
	static int m_iNextValidID ;

	void SetID();
};

#endif