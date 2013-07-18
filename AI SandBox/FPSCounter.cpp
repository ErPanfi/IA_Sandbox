#include "FPSCounter.h"
#include "Utils.h"
#include "FontManager.h"

#include <SFML/Graphics.hpp>

FPSCounter::FPSCounter()
{
	m_frames = 0;
	m_lastFrameCheck = m_clock.getElapsedTime().asSeconds();
}


FPSCounter::~FPSCounter()
{
}

void FPSCounter::Update()
{
	m_frames++;
	float fps=0.f;
	if ((fps = m_clock.getElapsedTime().asSeconds() - m_lastFrameCheck)>=1.f)
	{
		fps *= m_frames;
		m_fps = " FPS: " + NumberToString(fps);
		m_frames = 0;
		m_lastFrameCheck=m_clock.getElapsedTime().asSeconds();
	}
}

void FPSCounter::Draw(sf::RenderWindow& eRender)
{
	const sf::Font* font = FontManager::Istance()->GetFont(FontEnum::Font_Consola);
	sf::Text text(m_fps, (*font), 14);
	text.setPosition(0, eRender.getSize().y - 25.f);
	eRender.draw(text);
}