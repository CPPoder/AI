#include "stdafx.h"
#include "Window.hpp"


//Default Constructor
Window::Window(sf::Font *font)
	: mPosition(sf::Vector2f(300.f, 200.f)),
	  mWindowSize(sf::Vector2f(600.f, 400.f)),
	  mTitleBarHeight(35.f),
	  mRimThickness(2.f),
	  pFont(font)
{
	pBackgroundRectangle = new sf::RectangleShape;
	pBackgroundRectangle->setPosition(mPosition);
	pBackgroundRectangle->setSize(mWindowSize);
	pBackgroundRectangle->setFillColor(sf::Color::Black);

	pTitleBarRectangle = new sf::RectangleShape;
	pTitleBarRectangle->setPosition(mPosition.x, mPosition.y - mTitleBarHeight);
	pTitleBarRectangle->setSize(sf::Vector2f(mWindowSize.x, mTitleBarHeight));
	pTitleBarRectangle->setFillColor(sf::Color(150, 150, 150));

	pRimRectangle = new sf::RectangleShape;
	pRimRectangle->setPosition(mPosition - sf::Vector2f(0.f, mTitleBarHeight) - sf::Vector2f(mRimThickness, mRimThickness));
	pRimRectangle->setSize(mWindowSize + sf::Vector2f(0.f, mTitleBarHeight) + sf::Vector2f(2.f * mRimThickness, 2.f * mRimThickness));
	pRimRectangle->setFillColor(sf::Color(220, 220, 220));
	//pRimRectangle->setFillColor(sf::Color(75, 75, 200));

	pTitleText = new sf::Text("Title", *pFont, static_cast<unsigned int>(mTitleBarHeight * 0.53f));
	pTitleText->setColor(sf::Color::Black);
	pTitleText->setPosition(pTitleBarRectangle->getPosition() + sf::Vector2f(0.f, 0.7f * (mTitleBarHeight - static_cast<float>(pTitleText->getCharacterSize())) / 2.f) + sf::Vector2f(5.f, 0.f));
}

//Destructor
Window::~Window()
{
	delete pBackgroundRectangle;
	pBackgroundRectangle = nullptr;

	delete pTitleBarRectangle;
	pTitleBarRectangle = nullptr;

	delete pRimRectangle;
	pRimRectangle = nullptr;

	delete pTitleText;
	pTitleText = nullptr;
}


//Handle Events
void Window::handleEvents()
{

}

//Update
void Window::update(sf::Time frametime)
{

}

//Render
void Window::render(sf::RenderWindow *pRenderWindow)
{
	sf::View defaultView = pRenderWindow->getDefaultView();
	sf::View actualView = pRenderWindow->getView();
	pRenderWindow->setView(defaultView);

	pRenderWindow->draw(*pRimRectangle);
	pRenderWindow->draw(*pBackgroundRectangle);
	pRenderWindow->draw(*pTitleBarRectangle);
	pRenderWindow->draw(*pTitleText);

	pRenderWindow->setView(actualView);
}






