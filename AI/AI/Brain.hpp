#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <iostream>

#include "SFML\Graphics.hpp"

#include "mySFMLVectorFunctions.hpp"


class Brain
{
private:
	//static unsigned int counter1;
	//static unsigned int counter2;


public:
	Brain();
	~Brain();

	sf::Vector2f calculateWantedForce(); //Later with Arguments
	//void mutate(); //Maybe Parameter




};




#endif //BRAIN_HPP