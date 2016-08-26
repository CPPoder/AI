#include "stdafx.h"
#include "Brain.hpp"

//unsigned int Brain::counter1(0);
//unsigned int Brain::counter2(0);

///////////////////////////
//Constructors & Destructor


//DefaultConstructor
Brain::Brain()
{

}


//Destructor
Brain::~Brain()
{

}



////////////////////////
//Public Memberfunctions


//Calculate the wanted Force
sf::Vector2f Brain::calculateWantedForce()
{
	sf::Vector2f rnv = mySFML::dirtyRandNormalVector(50);
	/*if (rnv.y < 0)
	{
		counter1 += 1;
	}
	else
	{
		counter2 += 1;
	}

	std::cout << counter1 << "\t" << counter2 << std::endl;
	*/
	return (1000.f * rnv);
}