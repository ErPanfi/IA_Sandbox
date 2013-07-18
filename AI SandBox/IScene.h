#ifndef ISCENE_H
#define ISCENE_H

#include <sfml/Window.hpp>
#include <sfml/Graphics.hpp>

/*
	IScene. Pure Abstract class. 
	It must be a super class of every gamestate callable by the Application.h.
	A common base for MainMenu, Game, PauseMenu, Credits ... 
*/

class IScene
{
public:
	IScene(){}
	virtual ~IScene() {}

	virtual void	OnIdle() = 0;
	virtual void	OnDraw(sf::RenderWindow&) = 0;

};

#endif