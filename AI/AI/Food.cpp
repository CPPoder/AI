#include "stdafx.h"
#include "Food.hpp"


Food::Food()
	: Food::Food(sf::Vector2f(300.f, 300.f))
{
}

Food::Food(sf::Vector2f position)
{
	float size = 6.f;
	mCircleShape.setRadius(size);
	mCircleShape.setOrigin(size, size);
	mCircleShape.setPosition(position);
	mCircleShape.setFillColor(sf::Color(200, 125, 0));
}

Food::~Food()
{
}


void Food::update(sf::Time frametime)
{
}

void Food::render(sf::RenderWindow *renderWindow)
{
	renderWindow->draw(mCircleShape);
}

void Food::handleEvents()
{
}


void Food::setPosition(sf::Vector2f position)
{
	mCircleShape.setPosition(position);
}


sf::Vector2f Food::getPosition() const
{
	return mCircleShape.getPosition();
}
float Food::getRadius() const
{
	return mCircleShape.getRadius();
}