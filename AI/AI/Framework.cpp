#include "stdafx.h"
#include "Framework.hpp"

//Constructor
Framework::Framework()
{
	srand(time(0));

	mTimeFactor = 1.f;

	pArialFont = new sf::Font;
	pArialFont->loadFromFile("Fonts/arial.ttf");

	sf::Vector2u windowSize(1650, 950);
	sf::Vector2u worldSize(3000, 3000);
	pRenderWindow = new sf::RenderWindow(sf::VideoMode(windowSize.x, windowSize.y), "Artificial Intelligence");
	pRenderWindow->setPosition(sf::Vector2i(10, 10));
	pRenderWindow->setView(sf::View(sf::FloatRect(sf::Vector2f(0.f, 0.f), static_cast<sf::Vector2f>(windowSize))));
	pWorld = new World(worldSize, pArialFont);

	pTextFPS = new sf::Text("", *pArialFont, 20);
	pTextFPS->setPosition(5.f, 5.f);

	pTextTimeFactor = new sf::Text("TimeFactor: " + std::to_string(mTimeFactor), *pArialFont, 20);
	pTextTimeFactor->setPosition(5.f, 30.f);

	pClock = new sf::Clock;
	pClock->restart();
	mFPSTime = sf::Time::Zero;
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
		//Close
		if (mEvent.type == sf::Event::EventType::Closed)
		{
			pRenderWindow->close();
		}
		if (mEvent.type == sf::Event::EventType::KeyReleased)
		{
			if (mEvent.key.code == sf::Keyboard::Return)
			{
				pRenderWindow->close();
			}
		}
	}
}

void Framework::update()
{
	//Measuring Frametime
	mFrametime = pClock->restart();

	//Adjusting mTimeFactor
	float const adjustingTFConstant = 10.01f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Add))
	{
		mTimeFactor = mTimeFactor * pow(adjustingTFConstant, mFrametime.asSeconds());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Subtract))
	{
		mTimeFactor = mTimeFactor * pow(1 / adjustingTFConstant, mFrametime.asSeconds());
	}
	pTextTimeFactor->setString("TimeFactor: " + std::to_string(mTimeFactor));

	//Adjusting usedTimeFactor
	float usedTimeFactor = mTimeFactor;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
	{
		usedTimeFactor = 0.f;
	}
	
	//Determining FPS
	mFPSTime = mFPSTime + mFrametime;
	mFPSCounter = mFPSCounter + 1;
	if (mFPSTime.asSeconds() > 1.f)
	{
		mFPSTime = sf::Time::Zero;
		pTextFPS->setString("FPS: " + std::to_string(mFPSCounter));
		mFPSCounter = 0;
	}

	//Updating the world
	pWorld->update(usedTimeFactor * mFrametime);


	//Change View
	bool pressedZ = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z);
	bool pressedH = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H);
	bool pressedUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
	bool pressedDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
	bool pressedLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
	bool pressedRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);

	//Zoom
	if (pressedZ || pressedH)
	{
		float const zoomConstant = 15.f;
		float zoom = 1.f;
		if (pressedZ)
		{
			zoom = zoom * pow((1.f / zoomConstant), mFrametime.asSeconds());
		}
		if (pressedH)
		{
			zoom = zoom * pow(zoomConstant, mFrametime.asSeconds());
		}
		sf::View rwView = pRenderWindow->getView();
		rwView.zoom(zoom);
		pRenderWindow->setView(rwView);
	}
	
	//Move
	if (pressedUp || pressedDown || pressedLeft || pressedRight)
	{
		float const moveConstant = 0.8f;
		sf::Vector2f moveDirection = sf::Vector2f(0.f, 0.f);
		if (pressedUp)
		{
			moveDirection = moveDirection + sf::Vector2f(0.f, -1.f);
		}
		if (pressedDown)
		{
			moveDirection = moveDirection + sf::Vector2f(0.f, 1.f);
		}
		if (pressedRight)
		{
			moveDirection = moveDirection + sf::Vector2f(1.f, 0.f);
		}
		if (pressedLeft)
		{
			moveDirection = moveDirection + sf::Vector2f(-1.f, 0.f);
		}
		sf::View rwView = pRenderWindow->getView();
		float averageViewSize = (rwView.getSize().x + rwView.getSize().y) / 2.f;
		rwView.move(moveConstant * mFrametime.asSeconds() * averageViewSize * moveDirection);
		pRenderWindow->setView(rwView);
	}

}

void Framework::render()
{
	pRenderWindow->clear();

	//Render World
	pWorld->render(pRenderWindow);

	//Render DefaultViewThings
	sf::View currView = pRenderWindow->getView();
	pRenderWindow->setView(pRenderWindow->getDefaultView());
	pRenderWindow->draw(*pTextFPS);
	pRenderWindow->draw(*pTextTimeFactor);
	pRenderWindow->setView(currView);

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