#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <iostream>
#include <vector>

#include "SFML\Graphics.hpp"

#include "mySFMLVectorFunctions.hpp"


//////////////
//Class: Brain

class Brain
{
private:


public:
	Brain();
	virtual ~Brain();

	virtual void setInputFromSence() = 0;
	virtual sf::Vector2f calculateWantedForce() = 0;
	//virtual void mutate(); //Maybe Parameter

};



///////////////////
//Class: RandomBrain

class RandomBrain : public Brain
{
private:

public:
	RandomBrain();
	~RandomBrain() override;

	void setInputFromSence() override;
	sf::Vector2f calculateWantedForce() override;
};



//////////////////
//Class: ListBrain

class ListBrain : public Brain
{
private:
	std::vector<bool> mInputFromSence;
	std::vector<std::vector<bool>> mVectorOfOutputs;

public:
	ListBrain();
	~ListBrain() override;

	void setInputFromSence() override;
	sf::Vector2f calculateWantedForce() override;


};




#endif //BRAIN_HPP