#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "State.h"
#include <cassert>
#include <string>

/*
	Template class for a Finite State Machine (FSM). Type is the owner's type. 
	State type must be the same of FSM type.
	GlobalState and CurrentState are optional, but you have to set at least one.
*/
template<class Type>
class StateMachine{

private:
	//pointer to the agent owner
	Type* m_Owner;

	//3 states: current prev and a possible global(always called)
	State<Type>* m_CurrState;
	State<Type>* m_PrevState;
	State<Type>* m_GlobalState;

public:
	StateMachine(Type* owner):m_Owner(owner),
		m_CurrState(NULL),
		m_PrevState(NULL),
		m_GlobalState(NULL)
	{}

	//Init Methods
	inline void SetCurrentState(State<Type>* s) { m_CurrState = s;  }
	inline void SetPreviousState(State<Type>* s) { m_PrevState = s; }
	inline void SetGlobalState(State<Type>* s) { m_GlobalState = s; }

	void Update(){

		if (m_GlobalState)	m_GlobalState->Execute(m_Owner);

		if (m_CurrState)	m_CurrState->Execute(m_Owner);

	}

	void ChangeState(State<Type>* newState){

		m_PrevState = m_CurrState;

		if(m_CurrState) m_CurrState->Exit(m_Owner);

		m_CurrState = newState;

		if(newState) m_CurrState->Enter(m_Owner);
		
	}

	void RevertToPreviousState(){

		ChangeState(m_PrevState);

	}

	//Getters
	inline const State<Type>* CurrenState() const { return m_CurrState; }
	inline const State<Type>* PreviousState() const { return m_PrevState; }
	inline const State<Type>* GlobalState() const { return m_GlobalState; }

	//Check, true if the currState is equal to the argument
	inline bool IsInState(const State<Type>& compState)const
	{
		return ( m_CurrState && typeid(*m_CurrState)==typeid(compState));
	}

};

#endif