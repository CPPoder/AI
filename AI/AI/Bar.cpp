#include "stdafx.h"
#include "Bar.hpp"



Bar::Bar()
	: Bar::Bar(sf::Vector2f(), sf::Vector2f(), sf::Color(), sf::Color(), 0.f)
{
}

Bar::Bar(sf::Vector2f position, sf::Vector2f fullBarSize, sf::Color barColor, sf::Color lostBarColor, float fillQuotient)
	: mBarColor(barColor),
	  mLostBarColor(lostBarColor),
	  mPosition(position),
	  mSizeOfFullBar(fullBarSize),
	  mFillQuotient(fillQuotient)
{
	refresh();
}

Bar::~Bar()
{

}


void Bar::update(sf::Time frametime, sf::RenderWindow *pRenderWindow)
{
	
}

void Bar::render(sf::RenderWindow *renderWindow)
{
	renderWindow->draw(mBar);
	renderWindow->draw(mLostBar);
}

void Bar::handleEvents()
{
}


void Bar::setFillQuotient(float fillQuotient)
{
	mFillQuotient = fillQuotient;
	refresh();
}
void Bar::setPosition(sf::Vector2f position)
{
	mPosition = position;
	refresh();
}
void Bar::move(sf::Vector2f translation)
{
	mPosition = mPosition + translation;
	refresh();
}

float Bar::getFillQuotient() const
{
	return mFillQuotient;
}


void Bar::refresh()
{
	mBar.setFillColor(mBarColor);
	mLostBar.setFillColor(mLostBarColor);

	mBar.setPosition(mPosition);
	mBar.setSize(sf::Vector2f(mFillQuotient * mSizeOfFullBar.x, mSizeOfFullBar.y));

	mLostBar.setPosition(mPosition + sf::Vector2f(mBar.getSize().x, 0.f));
	mLostBar.setSize(sf::Vector2f((1 - mFillQuotient) * mSizeOfFullBar.x, mSizeOfFullBar.y));
}