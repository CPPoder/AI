#include "stdafx.h"
#include "World.hpp"


World::World()
	: World::World(sf::Vector2u(800, 800), nullptr)
{
}

World::World(sf::Vector2u worldSize, sf::Font *font)
	: mWorldSize(static_cast<sf::Vector2f>(worldSize)),
	  pFont(font),
	  mActualNumberOfCarnies(0),
	  mActualNumberOfHerbies(0),
	  mActualNumberOfFood(0),
	  mDataPresenter(pFont)
{
	mWorldBackground.setPosition(0.f, 0.f);
	mWorldBackground.setSize(mWorldSize);
	mWorldBackground.setFillColor(sf::Color(60, 60, 60));
	
	unsigned int const numOfHerbies = 100;
	unsigned int const numOfCarnies = 5;

	for (unsigned int i = 0; i < numOfHerbies; i++)
	{
		mListOfHerbivores.push_back(new Herbivore(sf::Vector2f(myMath::randIntervalf(0, static_cast<int>(mWorldSize.x)), myMath::randIntervalf(0, static_cast<int>(mWorldSize.y))), new USED_BRAIN));
	}
	for (unsigned int i = 0; i < numOfCarnies; i++)
	{
		mListOfCarnivores.push_back(new Carnivore(sf::Vector2f(myMath::randIntervalf(0, static_cast<int>(mWorldSize.x)), myMath::randIntervalf(0, static_cast<int>(mWorldSize.y))), new USED_BRAIN));
	}
	for (unsigned int i = 0; i < mNumOfFood; i++)
	{
		mListOfFood.push_back(new Food(sf::Vector2f(myMath::randIntervalf(0, static_cast<int>(mWorldSize.x)), myMath::randIntervalf(0, static_cast<int>(mWorldSize.y)))));
	}

	pWindow = new Window(pFont, sf::Vector2f(100.f, 200.f), sf::Vector2f(600.f, 400.f));
}

World::~World()
{
	for (auto food : mListOfFood)
	{
		delete food;
	}
	for (auto herb : mListOfHerbivores)
	{
		delete herb;
	}
	for (auto carn : mListOfCarnivores)
	{
		delete carn;
	}

	delete pWindow;
	pWindow = nullptr;
}

void World::update(sf::Time frametime, sf::RenderWindow *pRenderWindow)
{
	//Add frametime to mSimulationTime
	mSimulationTime = mSimulationTime + frametime;

	//Calculate what Creatures see
	calculateWhatCreaturesSee();

	//Update herbies and carnies
	for (auto herb : mListOfHerbivores)
	{
		herb->update(frametime, pRenderWindow);
	}
	for (auto carn : mListOfCarnivores)
	{
		carn->update(frametime, pRenderWindow);
	}

	//Domesticate perodic boundary conditions
	std::function<void(Creature*)> addPeriodicity = [this](Creature* creature) {
		sf::Vector2f pos = creature->getPosition();
		if (pos.x < 0.f) creature->setPosition(pos + sf::Vector2f(mWorldSize.x, 0.f));
		if (pos.y < 0.f) creature->setPosition(pos + sf::Vector2f(0.f, mWorldSize.y));
		if (pos.x > mWorldSize.x) creature->setPosition(pos - sf::Vector2f(mWorldSize.x, 0.f));
		if (pos.y > mWorldSize.y) creature->setPosition(pos - sf::Vector2f(0.f, mWorldSize.y));
	};
	for (auto herb : mListOfHerbivores)
	{
		addPeriodicity(herb);
	}
	for (auto carn : mListOfCarnivores)
	{
		addPeriodicity(carn);
	}

	//Herbies eat Food
	herbiesEatFood();

	//Carnies eat Herbies
	carniesEatHerbies();

	//Spawn Food
	spawnFood(frametime);

	//Creatures die without food
	creaturesDieWithoutFood();

	//CreaturesReproduce
	creaturesReproduce();

	//Check Actual Numbers of Creatures
	unsigned int newNumOfCarnies = mListOfCarnivores.size();
	unsigned int newNumOfHerbies = mListOfHerbivores.size();
	unsigned int newNumOfFood = mListOfFood.size();
	if ((newNumOfCarnies != mActualNumberOfCarnies) || (newNumOfHerbies != mActualNumberOfHerbies))
	{
		mDataListener.addCreatureNumberData(mSimulationTime, newNumOfCarnies, newNumOfHerbies, newNumOfFood);
		mActualNumberOfCarnies = newNumOfCarnies;
		mActualNumberOfHerbies = newNumOfHerbies;
		mActualNumberOfFood = newNumOfFood;
	}
	

	//Update Window
	if (pWindow != nullptr)
	{
		pWindow->update(frametime, pRenderWindow);
		bool windowShallBeClosed = pWindow->getCloseButtonReleased();
		if (windowShallBeClosed)
		{
			delete pWindow;
			pWindow = nullptr;
		}
	}

	//Feed Window with DrawStuff
	mDataPresenter.update();
	if (pWindow != nullptr && mDataPresenter.getHasChanged())
	{
		pWindow->clearDrawStuff();
		std::list<std::pair<sf::VertexArray, unsigned int>> listOfVertexArrays = mDataPresenter.getListOfVertexArrays();
		for (auto vertexArray : listOfVertexArrays)
		{
			pWindow->addVertexArray(new sf::VertexArray(vertexArray.first), vertexArray.second);
		}
		std::list<std::pair<sf::Text, unsigned int>> listOfTexts = mDataPresenter.getListOfTexts();
		for (auto text : listOfTexts)
		{
			pWindow->addText(new sf::Text(text.first), text.second);
		}
		mDataPresenter.usedAllNewData();
	}


}

void World::render(sf::RenderWindow *renderWindow)
{
	renderWindow->draw(mWorldBackground);
	for (auto food : mListOfFood)
	{
		food->render(renderWindow);
	}
	for (auto herb : mListOfHerbivores)
	{
		herb->render(renderWindow);
	}
	for (auto carn : mListOfCarnivores)
	{
		carn->render(renderWindow);
	}
	if (pWindow != nullptr)
	{
		pWindow->render(renderWindow);
	}
}

void World::handleEvents()
{

}


//Calculate what Creatures see
void World::calculateWhatCreaturesSee()
{
	//What Herbies See
	for (auto herb : mListOfHerbivores)
	{
		if (mListOfCarnivores.empty())
		{
			herb->setInputFromSence(std::vector<bool>(8, true));
		}
		else
		{
			//Find smallest distance
			sf::Vector2f herbPos = herb->getPosition();
			//sf::Vector2f distVec = mListOfCarnivores.front()->getPosition() - herbPos;
			sf::Vector2f distVec = periodicDistance(herbPos, mListOfCarnivores.front()->getPosition());
			float distance = mySFML::lengthOf(distVec);
			for (auto carn : mListOfCarnivores)
			{
				sf::Vector2f carnPos = carn->getPosition();
				//sf::Vector2f newDistVec = carnPos - herbPos;
				sf::Vector2f newDistVec = periodicDistance(herbPos, carnPos);
				float newDist = mySFML::lengthOf(newDistVec);
				if (newDist < distance)
				{
					distVec = newDistVec;
					distance = newDist;
				}
			}
			
			//Set Input With this Distance
			float sensitiveDistance = 300.f;
			unsigned int bitDepth = 4;
			float distVecX = distVec.x;
			float distVecY = distVec.y;

			float largestComponent = myMath::max(distVecX * myMath::sign(distVecX), distVecY * myMath::sign(distVecY)); //Cuts out a square
			float cuttingFactor = myMath::min((sensitiveDistance / largestComponent), 1.f);
			float cuttedDistVecX = cuttingFactor * distVecX;
			float cuttedDistVecY = cuttingFactor * distVecY;

			std::function<unsigned int(float)> inputTrafo = myMath::createIntervalBasedAffineTrafo(-sensitiveDistance, sensitiveDistance, 0.f, static_cast<float>(myMath::intPow(2, bitDepth) - 1));
			unsigned int UIinputX = static_cast<unsigned int>(inputTrafo(cuttedDistVecX) + 0.5);
			unsigned int UIinputY = static_cast<unsigned int>(inputTrafo(cuttedDistVecY) + 0.5);

			std::vector<bool> boolVecX = myMath::trafoUintToBoolVectorOfGivenSize(UIinputX, bitDepth);
			std::vector<bool> boolVecY = myMath::trafoUintToBoolVectorOfGivenSize(UIinputY, bitDepth);

			std::vector<bool> input = boolVecX;
			input.insert(input.end(), boolVecX.begin(), boolVecX.end());
			herb->setInputFromSence(input);
		}
	}


	//What Carnies See
	for (auto carn : mListOfCarnivores)
	{
		if (mListOfHerbivores.empty())
		{
			carn->setInputFromSence(std::vector<bool>(8, true));
		}
		else
		{
			//Find smallest distance
			sf::Vector2f carnPos = carn->getPosition();
			//sf::Vector2f distVec = mListOfHerbivores.front()->getPosition() - carnPos;
			sf::Vector2f distVec = periodicDistance(carnPos, mListOfHerbivores.front()->getPosition());
			float distance = mySFML::lengthOf(distVec);
			for (auto herb : mListOfHerbivores)
			{
				sf::Vector2f herbPos = herb->getPosition();
				//sf::Vector2f newDistVec = herbPos - carnPos;
				sf::Vector2f newDistVec = periodicDistance(carnPos, herbPos);
				float newDist = mySFML::lengthOf(newDistVec);
				if (newDist < distance)
				{
					distVec = newDistVec;
					distance = newDist;
				}
			}

			//Set Input With this Distance
			float sensitiveDistance = 300.f;
			unsigned int bitDepth = 4;
			float distVecX = distVec.x;
			float distVecY = distVec.y;

			float largestComponent = myMath::max(distVecX * myMath::sign(distVecX), distVecY * myMath::sign(distVecY)); //Cuts out a square
			float cuttingFactor = myMath::min((sensitiveDistance / largestComponent), 1.f);
			float cuttedDistVecX = cuttingFactor * distVecX;
			float cuttedDistVecY = cuttingFactor * distVecY;

			std::function<unsigned int(float)> inputTrafo = myMath::createIntervalBasedAffineTrafo(-sensitiveDistance, sensitiveDistance, 0.f, static_cast<float>(myMath::intPow(2, bitDepth) - 1));
			unsigned int UIinputX = static_cast<unsigned int>(inputTrafo(cuttedDistVecX) + 0.5);
			unsigned int UIinputY = static_cast<unsigned int>(inputTrafo(cuttedDistVecY) + 0.5);

			std::vector<bool> boolVecX = myMath::trafoUintToBoolVectorOfGivenSize(UIinputX, bitDepth);
			std::vector<bool> boolVecY = myMath::trafoUintToBoolVectorOfGivenSize(UIinputY, bitDepth);

			std::vector<bool> input = boolVecX;
			input.insert(input.end(), boolVecX.begin(), boolVecX.end());
			carn->setInputFromSence(input);
		}
	}

	/*
	std::vector<bool> inputFromSence = { true, false, true, false, false, true, true, false };
	for (auto herb : mListOfHerbivores)
	{
		herb->setInputFromSence(inputFromSence);
	}
	for (auto carn : mListOfCarnivores)
	{
		carn->setInputFromSence(inputFromSence);
	}
	*/
}


//Herbies eat Food
void World::herbiesEatFood()
{
	for (std::list<Herbivore*>::iterator herbIt = mListOfHerbivores.begin(); herbIt != mListOfHerbivores.end(); ++herbIt)
	{
		sf::Vector2f herbPos = (*herbIt)->getPosition();
		float herbRad = (*herbIt)->getRadius();
		for (std::list<Food*>::iterator foodIt = mListOfFood.begin(); foodIt != mListOfFood.end();)
		{
			sf::Vector2f foodPos = (*foodIt)->getPosition();
			float foodRad = (*foodIt)->getRadius();
			//if (mySFML::lengthOf(foodPos - herbPos) < (foodRad + herbRad))
			if (mySFML::lengthOf(periodicDistance(herbPos, foodPos)) < (foodRad + herbRad))
			{
				delete (*foodIt);
				foodIt = mListOfFood.erase(foodIt);
				(*herbIt)->addHealth(10.f);
			}
			else
			{
				++foodIt;
			}
		}
	}
}

//Carnies eat Herbies
void World::carniesEatHerbies()
{
	for (std::list<Carnivore*>::iterator carnIt = mListOfCarnivores.begin(); carnIt != mListOfCarnivores.end(); ++carnIt)
	{
		sf::Vector2f carnPos = (*carnIt)->getPosition();
		float carnRad = (*carnIt)->getRadius();
		for (std::list<Herbivore*>::iterator herbIt = mListOfHerbivores.begin(); herbIt != mListOfHerbivores.end();)
		{
			sf::Vector2f herbPos = (*herbIt)->getPosition();
			float herbRad = (*herbIt)->getRadius();
			//if (mySFML::lengthOf(herbPos - carnPos) < (herbRad + carnRad))
			if (mySFML::lengthOf(periodicDistance(carnPos, herbPos)) < (herbRad + carnRad))
			{
				delete (*herbIt);
				herbIt = mListOfHerbivores.erase(herbIt);
				(*carnIt)->addHealth(50.f);
			}
			else
			{
				++herbIt;
			}
		}
	}
}


//Spawn Food
void World::spawnFood(sf::Time frametime)
{
	unsigned int spawnableFood = 0;
	mTimeSinceLastFoodSpawn = mTimeSinceLastFoodSpawn + frametime;
	while (true)
	{
		if (mTimeSinceLastFoodSpawn >= mFoodSpawningTime)
		{
			mTimeSinceLastFoodSpawn = mTimeSinceLastFoodSpawn - mFoodSpawningTime;
			spawnableFood += 1;
		}
		else
		{
			break;
		}
	}
	for (unsigned int i = 0; i < spawnableFood; ++i)
	{
		mListOfFood.push_back(new Food(sf::Vector2f(myMath::randIntervalf(0, static_cast<int>(mWorldSize.x)), myMath::randIntervalf(0, static_cast<int>(mWorldSize.y)))));
	}
}


//Creatures die without food
void World::creaturesDieWithoutFood()
{
	for (std::list<Herbivore*>::iterator herbIt = mListOfHerbivores.begin(); herbIt != mListOfHerbivores.end();)
	{
		if ((*herbIt)->getHasDied())
		{
			delete (*herbIt);
			herbIt = mListOfHerbivores.erase(herbIt);
		}
		else
		{
			++herbIt;
		}
	}
	for (std::list<Carnivore*>::iterator carnIt = mListOfCarnivores.begin(); carnIt != mListOfCarnivores.end();)
	{
		if ((*carnIt)->getHasDied())
		{
			delete (*carnIt);
			carnIt = mListOfCarnivores.erase(carnIt);
		}
		else
		{
			++carnIt;
		}
	}
}


//Creatures Reproduce
void World::creaturesReproduce()
{
	//Carnivores
	for (std::list<Carnivore*>::iterator carnIt = mListOfCarnivores.begin(); carnIt != mListOfCarnivores.end(); ++carnIt)
	{
		if (!(*carnIt)->getAbleToReproduce())
		{
			continue;
		}
		for (std::list<Carnivore*>::iterator carnIt2 = carnIt; carnIt2 != mListOfCarnivores.end(); ++carnIt2)
		{
			if (carnIt == carnIt2)
			{
				continue;
			}
			if (!(*carnIt2)->getAbleToReproduce())
			{
				continue;
			}
			//if (mySFML::lengthOf((*carnIt)->getPosition() - (*carnIt2)->getPosition()) < ((*carnIt)->getRadius() + (*carnIt2)->getRadius()))
			if (mySFML::lengthOf(periodicDistance((*carnIt2)->getPosition(), (*carnIt)->getPosition())) < ((*carnIt)->getRadius() + (*carnIt2)->getRadius()))
			{
				std::cout << "Carni Reproduce" << std::endl;
				(*carnIt)->resetFertility();
				(*carnIt2)->resetFertility();
				if ((*carnIt)->getBrainPointer()->getBrainType() == BrainType::RANDOM_BRAIN)
				{
					RandomBrain *p1 = dynamic_cast<RandomBrain*>((*carnIt)->getBrainPointer());
					RandomBrain *p2 = dynamic_cast<RandomBrain*>((*carnIt2)->getBrainPointer());
					if ((p1 == nullptr) || (p2 == nullptr))
					{
						std::cout << "Error: World::creaturesReproduce() : dynamic_cast<RandomBrain*> gone wrong!" << std::endl;
						throw std::bad_exception();
					}
					mListOfCarnivores.push_back(new Carnivore(mySFML::meanVector((*carnIt)->getPosition(), (*carnIt2)->getPosition()), createNewRandomBrainForReproduction(p1, p2)));
				}
				if ((*carnIt)->getBrainPointer()->getBrainType() == BrainType::LIST_BRAIN)
				{
					ListBrain *p1 = dynamic_cast<ListBrain*>((*carnIt)->getBrainPointer());
					ListBrain *p2 = dynamic_cast<ListBrain*>((*carnIt2)->getBrainPointer());
					if ((p1 == nullptr) || (p2 == nullptr))
					{
						std::cout << "Error: World::creaturesReproduce() : dynamic_cast<ListBrain*> gone wrong!" << std::endl;
						throw std::bad_exception();
					}
					mListOfCarnivores.push_back(new Carnivore(mySFML::meanVector((*carnIt)->getPosition(), (*carnIt2)->getPosition()), createNewListBrainForReproduction(p1, p2)));
				}
				break;
			}
		}
	}



	//Herbivores
	for (std::list<Herbivore*>::iterator herbIt = mListOfHerbivores.begin(); herbIt != mListOfHerbivores.end(); ++herbIt)
	{
		if (!(*herbIt)->getAbleToReproduce())
		{
			continue;
		}
		for (std::list<Herbivore*>::iterator herbIt2 = herbIt; herbIt2 != mListOfHerbivores.end(); ++herbIt2)
		{
			if (herbIt == herbIt2)
			{
				continue;
			}
			if (!(*herbIt2)->getAbleToReproduce())
			{
				continue;
			}
			//if (mySFML::lengthOf((*herbIt)->getPosition() - (*herbIt2)->getPosition()) < ((*herbIt)->getRadius() + (*herbIt2)->getRadius()))
			if (mySFML::lengthOf(periodicDistance((*herbIt2)->getPosition(), (*herbIt)->getPosition())) < ((*herbIt)->getRadius() + (*herbIt2)->getRadius()))
			{
				std::cout << "Herbi Reproduce" << std::endl;
				(*herbIt)->resetFertility();
				(*herbIt2)->resetFertility();
				if ((*herbIt)->getBrainPointer()->getBrainType() == BrainType::RANDOM_BRAIN)
				{
					RandomBrain *p1 = dynamic_cast<RandomBrain*>((*herbIt)->getBrainPointer());
					RandomBrain *p2 = dynamic_cast<RandomBrain*>((*herbIt2)->getBrainPointer());
					if ((p1 == nullptr) || (p2 == nullptr))
					{
						std::cout << "Error: World::creaturesReproduce() : dynamic_cast<RandomBrain*> gone wrong!" << std::endl;
						throw std::bad_exception();
					}
					mListOfHerbivores.push_back(new Herbivore(mySFML::meanVector((*herbIt)->getPosition(), (*herbIt2)->getPosition()), createNewRandomBrainForReproduction(p1, p2)));
				}
				if ((*herbIt)->getBrainPointer()->getBrainType() == BrainType::LIST_BRAIN)
				{
					ListBrain *p1 = dynamic_cast<ListBrain*>((*herbIt)->getBrainPointer());
					ListBrain *p2 = dynamic_cast<ListBrain*>((*herbIt2)->getBrainPointer());
					if ((p1 == nullptr) || (p2 == nullptr))
					{
						std::cout << "Error: World::creaturesReproduce() : dynamic_cast<ListBrain*> gone wrong!" << std::endl;
						throw std::bad_exception();
					}
					mListOfHerbivores.push_back(new Herbivore(mySFML::meanVector((*herbIt)->getPosition(), (*herbIt2)->getPosition()), createNewListBrainForReproduction(p1, p2)));
				}
				break;
			}
		}
	}
}


//Calculate distance in periodic boundary conditions
sf::Vector2f World::periodicDistance(sf::Vector2f creature1Pos, sf::Vector2f creature2Pos) const
{
	sf::Vector2f distVec = creature2Pos - creature1Pos;

	float distX = distVec.x;
	if (distX > (mWorldSize.x / 2.f))
	{
		distX = distX - mWorldSize.x;
	}
	else if (distX < -(mWorldSize.x / 2.f))
	{
		distX = distX + mWorldSize.x;
	}

	float distY = distVec.y;
	if (distY > (mWorldSize.y / 2.f))
	{
		distY = distY - mWorldSize.y;
	}
	else if (distY < -(mWorldSize.y / 2.f))
	{
		distY = distY + mWorldSize.y;
	}

	return sf::Vector2f(distX, distY);
}



//Check for overlap (Does maybe not work right, if one creatures are at opposite sides)
bool World::checkForOverlap(Creature *creature1, Creature *creature2) const
{
	if (mySFML::lengthOf(creature1->getPosition() - creature2->getPosition()) < (creature1->getRadius() + creature2->getRadius()))
	{
		std::cout << "Overlap!!!" << std::endl;
		return true;
	}
	else
	{
		return false;
	}
	
}