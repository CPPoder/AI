#ifndef FRAMEWORK_HPP
#define FRAMEWORK_HPP

#include <iostream>
#include <cstdlib>

#include "SFML\Graphics.hpp"

#include "World.hpp"


class Framework
{
private:
	sf::RenderWindow *pRenderWindow;

	World *pWorld;

	sf::Clock *pClock;
	sf::Time mFrametime = sf::Time();

	void handleEvents();
	void update();
	void render();


public:
	Framework();
	~Framework();

	void run();

};



#endif