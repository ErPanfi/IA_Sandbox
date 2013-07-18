#include "GameScene.h"
#include "Agent.h"

GameScene::GameScene()
{
	m_agent = new Agent();
}


GameScene::~GameScene()
{
	delete m_agent;
}

void GameScene::OnIdle()
{
	m_agent->Update();
}

void GameScene::OnDraw(sf::RenderWindow& kRender)
{
	m_agent->OnDraw(kRender);
}