#include "stdafx.h"
#include "Brain.hpp"



///////////////////////
//Implementation: Brain

//DefaultConstructor
Brain::Brain()
{
}

//Destructor
Brain::~Brain()
{
}







/////////////////////////////
//Implementation: RandomBrain

//DefaultConstructor
RandomBrain::RandomBrain()
{

}

//Destructor
RandomBrain::~RandomBrain()
{

}

//Set Input from Sence
void RandomBrain::setInputFromSence()
{

}

//Calculate the wanted Force
sf::Vector2f RandomBrain::calculateWantedForce()
{
	sf::Vector2f rnv = mySFML::dirtyRandNormalVector(50);
	return (1000.f * rnv);
}









/////////////////////////////
//Implementation: ListBrain

//DefaultConstructor
ListBrain::ListBrain()
{

}

//Destructor
ListBrain::~ListBrain()
{

}

//Set Input from Sence
void ListBrain::setInputFromSence()
{

}

//Calculate the wanted Force
sf::Vector2f ListBrain::calculateWantedForce()
{
	return sf::Vector2f();
}