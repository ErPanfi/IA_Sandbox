#ifndef LOADINGSCENE_H
#define LOADINGSCENE_H

#include "IScene.h"

class LoadingScene : public IScene
{
public:
	LoadingScene();
	virtual ~LoadingScene();

	virtual void	OnIdle();
	virtual void	OnDraw(sf::RenderWindow&);
};

#endif
