#include <map>
#include <iostream>
#include <sfml/Graphics/RenderWindow.hpp>
#include "SceneEnum.h"
#include "FPSCounter.h"

class IScene;

class Application
{
public:
	static Application* Istance()
	{
		static Application istance;
		return &istance;
	}

	void Init(bool fullscreen = false);
	void Destroy(void);

	void							Run();
	void							Render();

	// ACCESSORS
	void							SetScene(const SceneEnum eScene, const bool bDeleteCurrent = false);
	void							Exit(const bool ignoreExitStep = false);

	inline const sf::RenderWindow* 	Window() const { return m_window; }
	IScene*							GetScene(const SceneEnum eScene);
	inline IScene*					GetCurrentScene() const { return m_currentScene; }
	inline SceneEnum				GetCurrentSceneName() const { return m_currentSceneName; }
	
	//Input
	inline bool						IsInputAvaible()
									{
										return m_clock.getElapsedTime().asSeconds() >= m_inputPauseTime; 
									}

	inline void						PauseInput()
									{  
										m_inputPauseTime = m_clock.getElapsedTime().asSeconds() + 0.15f;
									}

protected:
	Application(){}
	virtual ~Application(){}
	
	Application(const Application&);
	Application& operator=(const Application&);

private:

	typedef std::map<SceneEnum, IScene*> SceneMap;
	SceneMap m_scenes;

	sf::Clock					m_clock;
	float						m_inputPauseTime;
	FPSCounter					m_fpsCounter;

	sf::RenderWindow*			m_window;

	IScene*						m_currentScene;
	SceneEnum					m_currentSceneName;


};

