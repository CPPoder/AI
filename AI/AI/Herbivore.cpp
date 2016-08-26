#include "stdafx.h"
#include "Herbivore.hpp"



Herbivore::Herbivore()
	: Herbivore::Herbivore(sf::Vector2f(200.f, 200.f))
{
}

Herbivore::Herbivore(sf::Vector2f position)
	: Creature::Creature(position, sf::Color::Green, 10.f)
{
}


Herbivore::~Herbivore()
{

}


/*
void Herbivore::update()
{

}
*/
/*
void Herbivore::render(sf::RenderWindow *renderWindow)
{

}
*/
/*
void Herbivore::handleEvents()
{

}
*/