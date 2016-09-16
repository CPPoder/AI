#include "stdafx.h"
#include "Carnivore.hpp"



Carnivore::Carnivore()
	: Carnivore::Carnivore(sf::Vector2f(200.f, 200.f), new RandomBrain)
{
}

Carnivore::Carnivore(sf::Vector2f position, Brain *brain)
	: Creature::Creature(position, sf::Color::Red, 15.f, brain)
{
}

Carnivore::~Carnivore()
{

}

/*
void Carnivore::update()
{

}
*/
/*
void Carnivore::render(sf::RenderWindow *renderWindow)
{

}
*/
/*
void Carnivore::handleEvents()
{

}
*/