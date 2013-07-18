#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H

#include <sfml/Graphics/RenderWindow.hpp>

class FPSCounter
{
public:
	FPSCounter();
	~FPSCounter();

	void Update();
	void Draw(sf::RenderWindow&);

private:
	sf::Clock					m_clock;
	
	int							m_frames;
	float						m_lastFrameCheck;
	std::string					m_fps;

};

#endif