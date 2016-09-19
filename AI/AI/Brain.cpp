#include "stdafx.h"
#include "Brain.hpp"


//////////////////
//Class: BrainType

BrainType::BrainType()
{
}

BrainType::BrainType(BrainType const & brainType)
	: mTypeNum(brainType.mTypeNum)
{
}

BrainType::BrainType(unsigned int typeNum)
	: mTypeNum(typeNum)
{
}

BrainType::~BrainType()
{
}

BrainType& BrainType::operator=(BrainType const & other)
{
	mTypeNum = other.mTypeNum;
	return *this;
}

unsigned int BrainType::getTypeNum() const
{
	return mTypeNum;
}

const BrainType BrainType::BRAIN = BrainType(0);
const BrainType BrainType::RANDOM_BRAIN = BrainType(1);
const BrainType BrainType::LIST_BRAIN = BrainType(2);

bool operator==(BrainType type1, BrainType type2)
{
	return (type1.getTypeNum() == type2.getTypeNum());
}







///////////////////////
//Implementation: Brain

//DefaultConstructor
Brain::Brain()
	: mBrainType(BrainType::BRAIN)
{
}

//Destructor
Brain::~Brain()
{
}

//Get BrainType
BrainType Brain::getBrainType() const
{
	return mBrainType;
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
	mBrainType = BrainType::RANDOM_BRAIN;
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
ListBrain::ListBrain(bool createVectorOfOutputs)
	: ListBrain::ListBrain(300.f, createVectorOfOutputs)
{
}

//Constructor
ListBrain::ListBrain(float maximalForce, bool createVectorOfOutputs)
{
	//Set mMaximalForce
	mMaximalForce = maximalForce;

	//Set BrainType
	mBrainType = BrainType::LIST_BRAIN;

	//Initialize mVectorOfOutputs
	mBitDepth = 4;
	mNumberOfPossibleOutputs = 256; //2^(4*2)
	if (createVectorOfOutputs)
	{
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
	}
	


	//Initialize mInputFromSence
	for (unsigned int inputBit = 0; inputBit < 8; inputBit++)
	{
		mInputFromSence.push_back(false);
	}
	mInputFromSence.shrink_to_fit();

	//Initialize mOutputDAConversionTrafo
	mOutputDAConversionTrafo = myMath::createIntervalBasedAffineTrafo(0, 15, -mMaximalForce, maximalForce);
	
}
/*
ListBrain::ListBrain(std::vector<std::vector<bool>> vectorOfOutputs)
	: ListBrain::ListBrain(vectorOfOutputs, 300.f)
{
}

ListBrain::ListBrain(std::vector<std::vector<bool>> vectorOfOutputs, float maximalForce)
{
	//Set mMaximalForce
	mMaximalForce = maximalForce;

	//Initialize mVectorOfOutputs
	mVectorOfOutputs = vectorOfOutputs;


	//Initialize mInputFromSence
	for (unsigned int inputBit = 0; inputBit < 8; inputBit++)
	{
		mInputFromSence.push_back(false);
	}
	mInputFromSence.shrink_to_fit();

	//Initialize mOutputDAConversionTrafo
	mOutputDAConversionTrafo = myMath::createIntervalBasedAffineTrafo(0, 15, -mMaximalForce, maximalForce);
}
*/

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

//Set Vector of Outputs
void ListBrain::setVectorOfOutputs(std::vector<std::vector<bool>> const & vectorOfOutputs)
{
	mVectorOfOutputs = vectorOfOutputs;
}

std::vector<std::vector<bool>>* ListBrain::getVectorOfOutputsPointer()
{
	return &mVectorOfOutputs;
}







//////////////////
//Public Functions

RandomBrain* createNewRandomBrainForReproduction(RandomBrain *brain1, RandomBrain *brain2)
{
	return new RandomBrain;
}

ListBrain* createNewListBrainForReproduction(ListBrain *brain1, ListBrain *brain2)
{
	//Check Sizes of VectorsOfOutputs
	std::vector<std::vector<bool>>* vectorOfOutputs1 = brain1->getVectorOfOutputsPointer();
	std::vector<std::vector<bool>>* vectorOfOutputs2 = brain2->getVectorOfOutputsPointer();
	unsigned int numOfOut1 = vectorOfOutputs1->size();
	unsigned int numOfOut2 = vectorOfOutputs2->size();
	unsigned int numOfIn1 = vectorOfOutputs1->at(0).size();
	unsigned int numOfIn2 = vectorOfOutputs2->at(0).size();
	if ((numOfOut1 != numOfOut2) || (numOfIn1 != numOfIn2))
	{
		std::cout << "Error: createNewBrainForReproduction(ListBrain*, ListBrain*) : The two input ListBrains are not compatible!" << std::endl;
		throw std::bad_exception();
	}

	//Mix the vectorsOfOutputs
	std::vector<std::vector<bool>> newVecOfOutputs = *vectorOfOutputs1;
	for (unsigned int i = 0; i < numOfOut1; i++)
	{
		for (unsigned int j = 0; j < numOfIn1; j++)
		{
			bool changeVal = myMath::randBool();
			if (changeVal)
			{
				newVecOfOutputs.at(i).at(j) = vectorOfOutputs2->at(i).at(j);
			}
		}
	}

	//Create new Brain and return Pointer
	ListBrain *listBrain = new ListBrain(false);
	listBrain->setVectorOfOutputs(newVecOfOutputs);
	return listBrain;
}