#ifndef DATALISTENER_HPP
#define DATALISTENER_HPP

#include "SFML\Graphics.hpp"

#include <iostream>
#include <vector>
#include <utility>

#include "DataPresenter.hpp"


class DataListener
{
private:
	std::vector<std::pair<sf::Time, sf::Vector3<unsigned int>>> mVecOf_Time_CreatureNumb_Pairs;

	bool mNewData;


public:
	DataListener();
	~DataListener();

	void addCreatureNumberData(sf::Time time, unsigned int numberOfCarnivores, unsigned int numberOfHerbivores, unsigned int numberOfFood);
	

friend class DataPresenter;
};








#endif //DATALISTENER_HPP