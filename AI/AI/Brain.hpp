#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <iostream>
#include <vector>
#include <functional>

#include "SFML\Graphics.hpp"

#include "mySFMLVectorFunctions.hpp"
#include "myUsefulMath.hpp"


//////////////////
//Class: BrainType

class BrainType
{
private:
	unsigned int mTypeNum;

public:
	BrainType();
	BrainType(BrainType const & brainType);
	BrainType(unsigned int typeNum);
	~BrainType();
	BrainType& operator=(BrainType const & other);

	static const BrainType BRAIN;
	static const BrainType RANDOM_BRAIN;
	static const BrainType LIST_BRAIN;

	unsigned int getTypeNum() const;
};

bool operator==(BrainType type1, BrainType type2);






//////////////
//Class: Brain

class Brain
{
protected:
	float mMaximalForce;
	BrainType mBrainType;

public:
	Brain();
	virtual ~Brain();

	virtual void setInputFromSence(std::vector<bool> input) = 0;
	virtual sf::Vector2f calculateWantedForce() = 0;
	//virtual void mutate(); //Maybe Parameter

	BrainType getBrainType() const;

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
	ListBrain(bool createVectorOfOutputs = true);
	ListBrain(float maximalForce, bool createVectorOfOutputs = true);
	/*
	ListBrain(std::vector<std::vector<bool>> vectorOfOutputs);
	ListBrain(std::vector<std::vector<bool>> vectorOfOutputs, float maximalForce);
	*/
	~ListBrain() override;

	void setInputFromSence(std::vector<bool> input) override;
	sf::Vector2f calculateWantedForce() override;

	void setVectorOfOutputs(std::vector<std::vector<bool>> const & vectorOfOutputs);

	std::vector<std::vector<bool>>* getVectorOfOutputsPointer();


};






//////////////////
//Public Functions

RandomBrain* createNewRandomBrainForReproduction(RandomBrain *brain1, RandomBrain *brain2);

ListBrain* createNewListBrainForReproduction(ListBrain *brain1, ListBrain *brain2);




#endif //BRAIN_HPP