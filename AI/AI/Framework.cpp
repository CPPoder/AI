#include "stdafx.h"
#include "Framework.hpp"

//Constructor
Framework::Framework()
{
	srand(time(0));

	sf::Vector2u windowSize(1400, 900);
	pRenderWindow = new sf::RenderWindow(sf::VideoMode(windowSize.x, windowSize.y), "Artificial Intelligence");
	pWorld = new World(windowSize);

	pClock = new sf::Clock;
	pClock->restart();
}

//Destructor
Framework::~Framework()
{
	delete pRenderWindow;
	pRenderWindow = nullptr;

	delete pWorld;
	pWorld = nullptr;

	delete pClock;
	pClock = nullptr;
}


//HandleEvents, Update, Render
void Framework::handleEvents()
{
	sf::Event mEvent;
	while (pRenderWindow->pollEvent(mEvent))
	{
		if (mEvent.type == sf::Event::EventType::Closed)
		{
			pRenderWindow->close();
		}
	}
}

void Framework::update()
{
	pWorld->update(pClock->restart());
}

void Framework::render()
{
	pRenderWindow->clear();
	pWorld->render(pRenderWindow);
	pRenderWindow->display();
}


//Run
void Framework::run()
{
	while (pRenderWindow->isOpen())
	{
		handleEvents();
		update();
		render();
	}
}