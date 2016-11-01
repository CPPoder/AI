#include "stdafx.h"
#include "DataListener.hpp"


DataListener::DataListener()
	: mNewData(true)
{
}


DataListener::~DataListener()
{
}



void DataListener::addCreatureNumberData(sf::Time time, unsigned int numberOfCarnivores, unsigned int numberOfHerbivores, unsigned int numberOfFood)
{
	mVecOf_Time_CreatureNumb_Pairs.push_back(std::pair<sf::Time, sf::Vector3<unsigned int>>(time, sf::Vector3<unsigned int>(numberOfCarnivores, numberOfHerbivores, numberOfFood)));
	mNewData = true;
	//std::cout << time.asSeconds() << '\t' << numberOfCarnivores << '\t' << numberOfHerbivores << '\t' << numberOfFood << std::endl;
}