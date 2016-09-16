#include "stdafx.h"
#include "Herbivore.hpp"



Herbivore::Herbivore()
	: Herbivore::Herbivore(sf::Vector2f(200.f, 200.f), new RandomBrain)
{
}

Herbivore::Herbivore(sf::Vector2f position, Brain *brain)
	: Creature::Creature(position, sf::Color::Green, 10.f, brain)
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