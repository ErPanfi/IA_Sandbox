#include "LoadingScene.h"
#include "FontManager.h"
#include "Application.h"

LoadingScene::LoadingScene()
{
	FontManager::Istance()->Init();
}

LoadingScene::~LoadingScene()
{
	FontManager::Istance()->Destroy();
}

void LoadingScene::OnIdle()
{
	Application::Istance()->SetScene(SceneEnum::Scene_MainMenu);
}

void LoadingScene::OnDraw(sf::RenderWindow& kRender)
{
	sf::CircleShape circle = sf::CircleShape(10.0f);
	kRender.draw(circle);
}
