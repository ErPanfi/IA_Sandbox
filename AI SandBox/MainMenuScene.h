#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include "IScene.h"
#include <sfml/Graphics.hpp>

class MainMenuScene : public IScene
{
public:
	MainMenuScene();
	~MainMenuScene();

	void		OnDraw(sf::RenderWindow&);
	void		OnIdle();

private:
	void AssignMenuText(const sf::Font*, const std::string&, int);

	const static int	m_elements = 4;
	sf::Vector2i		m_pos;	//Top-Left Corner of the menu
	int					m_selected;
	sf::Text			m_menu[m_elements];
	sf::Text			m_shadows[m_elements];
	sf::Color			m_cNormal;
	sf::Color			m_cSelected;

};

#endif