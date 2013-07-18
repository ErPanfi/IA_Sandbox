#include "MainMenuScene.h"
#include "Application.h"
#include "FontEnum.h"
#include "FontManager.h"

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

MainMenuScene::MainMenuScene()
{

	m_cNormal = sf::Color::White;
	m_cSelected = sf::Color::Yellow;

	const sf::Font* font = FontManager::Istance()->GetFont(FontEnum::Font_Consola);
	AssignMenuText(font, "AStar", 0);
	AssignMenuText(font, "Gioco del 15", 1);
	AssignMenuText(font, "Miner", 2);
	AssignMenuText(font, "Exit", 3);

	float maxWidth = 0.f;
	float maxHeight = 0.f;

	for (int i  = 0; i < m_elements ; i++)
	{
		maxWidth = (m_menu[i].getGlobalBounds().width > maxWidth)  ? m_menu[i].getGlobalBounds().width : maxWidth;
		maxHeight = (m_menu[i].getGlobalBounds().height > maxHeight) ? m_menu[i].getGlobalBounds().height : maxHeight;
	}

	m_pos = sf::Vector2i((int)((Application::Istance()->Window()->getSize().x * 0.5f ) - (maxWidth * 0.5f)), 
						(int)(Application::Istance()->Window()->getSize().y * 0.5f - (maxHeight * 0.5f * m_elements)));
	
	for (int i  = 0; i < m_elements ; i++)
	{
		m_menu[i].setPosition(sf::Vector2f(m_pos.x + ((maxWidth - m_menu[i].getGlobalBounds().width) * 0.5f) , 
											m_pos.y + maxHeight*i));
		m_shadows[i].setPosition(sf::Vector2f(m_menu[i].getPosition().x + 2.f, m_menu[i].getPosition().y + 2.f));
		m_shadows[i].setColor(sf::Color::Black);
	}

	m_selected = 0;
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::AssignMenuText(const sf::Font* font, const std::string& name, int pos)
{
	m_menu[pos] = sf::Text(name, (*font), 26U);
	m_shadows[pos] = sf::Text(name, (*font), 26U);
}

void MainMenuScene::OnDraw(sf::RenderWindow& renderWindow)
{
	for (int i  = 0; i < m_elements ; i++)
	{
		renderWindow.draw(m_shadows[i]);
		m_menu[i].setColor( ( i == m_selected) ? m_cSelected : m_cNormal );
		renderWindow.draw(m_menu[i]);
	}
}

void MainMenuScene::OnIdle()
{
	if (!Application::Istance()->IsInputAvaible())
		return;

	m_pos = sf::Mouse::getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) >= 50.f )
	{
		Application::Istance()->PauseInput();
		m_selected = (m_selected == m_elements-1) ? 0 : m_selected + 1 ;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) <= -50.f )
	{
		Application::Istance()->PauseInput();
		m_selected = (m_selected == 0) ? m_elements-1 : m_selected -1 ;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)		//Enter pressed
		|| sf::Joystick::isButtonPressed(0,2)		//'X' button
		|| sf::Joystick::isButtonPressed(0,11))	//'Start' Button
	{
		Application::Istance()->PauseInput();

		switch (m_selected)
		{
			case 0:
				Application::Istance()->SetScene(SceneEnum::Scene_AStar);
				break;
			
			case 1:
				Application::Istance()->SetScene(SceneEnum::Scene_Gioco15);
				break;
			
			case 2:
				Application::Istance()->SetScene(SceneEnum::Scene_Miner);
				break;
			
			case 3:
				Application::Istance()->Exit();
				break;

			default:
				break;
		}
	}
}
