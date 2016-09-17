#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <iostream>
#include <vector>
#include <functional>

#include "SFML\Graphics.hpp"

#include "mySFMLVectorFunctions.hpp"
#include "myUsefulMath.hpp"


//////////////
//Class: Brain

class Brain
{
protected:
	float mMaximalForce;

public:
	Brain();
	virtual ~Brain();

	virtual void setInputFromSence(std::vector<bool> input) = 0;
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
	RandomBrain(float maximalForce);
	~RandomBrain() override;

	void setInputFromSence(std::vector<bool> input) override;
	sf::Vector2f calculateWantedForce() override;
};



//////////////////
//Class: ListBrain

class ListBrain : public Brain
{
private:
	unsigned int mBitDepth;
	unsigned int mNumberOfPossibleOutputs;
	std::vector<bool> mInputFromSence;
	std::vector<std::vector<bool>> mVectorOfOutputs;

	std::function<float(int)> mOutputDAConversionTrafo;

public:
	ListBrain();
	ListBrain(float maximalForce);
	~ListBrain() override;

	void setInputFromSence(std::vector<bool> input) override;
	sf::Vector2f calculateWantedForce() override;


};




#endif //BRAIN_HPP