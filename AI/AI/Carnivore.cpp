#include "stdafx.h"
#include "Carnivore.hpp"



Carnivore::Carnivore()
	: Carnivore::Carnivore(sf::Vector2f(200.f, 200.f))
{
}

Carnivore::Carnivore(sf::Vector2f position)
	: Creature::Creature(position, sf::Color::Red)
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