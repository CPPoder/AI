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

	sf::Font *pArialFont;

	World *pWorld;
	sf::Text *pTextFPS;
	sf::Text *pTextTimeFactor;

	sf::Clock *pClock;
	sf::Time mFrametime = sf::Time();
	sf::Time mFPSTime;
	unsigned int mFPSCounter;
	float mTimeFactor;

	void handleEvents();
	void update();
	void render();


public:
	Framework();
	~Framework();

	void run();

};



#endif