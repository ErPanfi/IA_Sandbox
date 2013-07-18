#include "Agent.h"
#include "SteeringBehaviors.h"

int Agent::m_iNextValidID = 0;

Agent::Agent() : m_maxSpeed(10.f),
				m_pos(Vector2::ZERO),
				m_speed(Vector2::ZERO),
				m_facing(Vector2::ZERO),
				m_AgentColor(sf::Color::Blue)
{
	SetID();

	m_FSM = new StateMachine<Agent>(this);
	m_FSM->SetPreviousState(NULL);

	m_steer = new SteeringBehaviors(this);
}

Agent::Agent(float maxSpeed, Vector2 pos, Vector2 facing, Vector2 speed)
						: m_maxSpeed(maxSpeed),
							m_pos(pos),
							m_speed(speed),
							m_facing(facing),
							m_AgentColor(sf::Color::Blue)
{
	SetID();
}

void Agent::SetID()
{
	m_ID = m_iNextValidID;
	m_iNextValidID++;
}

Agent::~Agent()
{
	delete m_steer;
	delete m_FSM;
}

void Agent::Update()
{
	m_FSM->Update();

	m_steer->Calculate();
	m_speed += m_steer->GetForce();

	m_facing = (m_steer->GetTarget() - m_pos).NormalizeCopy();
	
	m_pos += m_speed;
}

void Agent::OnDraw(sf::RenderWindow& kRender)
{
	sf::CircleShape circle = sf::CircleShape(5.5f);
	circle.setPosition(m_pos.x,m_pos.y);
	circle.setFillColor(m_AgentColor);
	kRender.draw(circle);
	
	//Facing
	sf::VertexArray v_array;
	v_array.append(sf::Vertex(sf::Vector2f(m_pos.x, m_pos.y) , sf::Color::Yellow));
	v_array.append(sf::Vertex(sf::Vector2f(m_pos.x + m_facing.x * 10.f, m_pos.y + m_facing.y * 10.f) , sf::Color::Yellow));
	v_array.setPrimitiveType(sf::Lines);
}

