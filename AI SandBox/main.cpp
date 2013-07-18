#include <iostream>
#include "Application.h"

int main (int argc, char * const argv[]) {
   
	Application* game = Application::Istance();
	
	game->Init();
	
	game->Run();
	
	game->Destroy();
	
	exit(0);
}

/*#include "SFML/Graphics.hpp"
 
int main()
{
    sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "RenderWindow", sf::Style::Titlebar | sf::Style::Close); 
    sf::Vector2u size(400, 400);
 
    Window.setSize(size); 
    Window.setTitle("Awesome Pawesome!"); 
    Window.setPosition(sf::Vector2i(100, 100));
 
    while(Window.isOpen())
    {
        sf::Event Event; 
        while(Window.pollEvent(Event))
        {
            if(Event.type == sf::Event::Closed || Event.key.code == sf::Keyboard::Escape)
                Window.close();
        }
 
        Window.display();
    }
    return 0; 
}*/



