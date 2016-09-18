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
	: RandomBrain::RandomBrain(300.f)
{
}

//Constructor
RandomBrain::RandomBrain(float maximalForce)
{
	mMaximalForce = maximalForce;
}

//Destructor
RandomBrain::~RandomBrain()
{

}

//Set Input from Sence
void RandomBrain::setInputFromSence(std::vector<bool> input)
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
	: ListBrain::ListBrain(300.f)
{
}

//Constructor
ListBrain::ListBrain(float maximalForce)
{
	//Set mMaximalForce
	mMaximalForce = maximalForce;

	//Initialize mVectorOfOutputs
	mBitDepth = 4;
	mNumberOfPossibleOutputs = 256; //2^(4*2)

	for (unsigned int outputNum = 0; outputNum < mNumberOfPossibleOutputs; outputNum++)
	{
		std::vector<bool> output;
		for (unsigned int outputBit = 0; outputBit < 8; outputBit++)
		{
			output.push_back(myMath::randBool());
		}
		output.shrink_to_fit();
		mVectorOfOutputs.push_back(output);
	}
	mVectorOfOutputs.shrink_to_fit();


	//Initialize mInputFromSence
	for (unsigned int inputBit = 0; inputBit < 8; inputBit++)
	{
		mInputFromSence.push_back(0);
	}
	mInputFromSence.shrink_to_fit();

	//Initialize mOutputDAConvertationTrafo
	mOutputDAConversionTrafo = myMath::createIntervalBasedAffineTrafo(0, 15, -mMaximalForce, maximalForce);
	
}

//Destructor
ListBrain::~ListBrain()
{

}

//Set Input from Sence
void ListBrain::setInputFromSence(std::vector<bool> input)
{
	if (input.size() == 8)
	{
		mInputFromSence = input;
	}
	else
	{

		std::cout << "Error: ListBrain::setInputFromSence(std::vector<bool>) recognized wrong input vector size! Namely: " << input.size() << std::endl;
	}
}

//Calculate the wanted Force
sf::Vector2f ListBrain::calculateWantedForce()
{
	//Determine right output
	unsigned int posOfOutput = myMath::trafoBoolVectorToUInt(mInputFromSence);
	std::vector<bool> output = mVectorOfOutputs.at(posOfOutput);

	//Split output into vector components
	std::vector<bool> outX;
	std::vector<bool> outY;
	outX.push_back(output.at(0));
	outX.push_back(output.at(1));
	outX.push_back(output.at(2));
	outX.push_back(output.at(3));
	outY.push_back(output.at(4));
	outY.push_back(output.at(5));
	outY.push_back(output.at(6));
	outY.push_back(output.at(7));

	int xInt = myMath::trafoBoolVectorToUInt(outX);
	int yInt = myMath::trafoBoolVectorToUInt(outY);

	float xForce = mOutputDAConversionTrafo(xInt);
	float yForce = mOutputDAConversionTrafo(yInt);

	return sf::Vector2f(xForce, yForce);
}