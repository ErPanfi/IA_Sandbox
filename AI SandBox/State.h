#ifndef STATE_H
#define STATE_H

/*
	Template class to create State. Type is the type of the state's owner.
*/
template <class Type>
class State  
{
public:
	virtual ~State(){}

	virtual void Enter(Type*) = 0;

	virtual void Execute(Type*) = 0;

	virtual void Exit(Type*) = 0;
};


#endif
