#ifndef WORKER_FSM_SCENE
#define WORKER_FSM_SCENE

#include "iscene.h"

class WorkerFSMScene :
	public IScene
{
public:
	WorkerFSMScene() {};
	~WorkerFSMScene() {};

	virtual void	OnIdle();
	virtual void	OnDraw(sf::RenderWindow&);
};

#endif