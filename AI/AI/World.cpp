#include "stdafx.h"
#include "World.hpp"


World::World()
	: World::World(sf::Vector2u(800, 800))
{
}

World::World(sf::Vector2u worldSize)
	: mWorldSize(static_cast<sf::Vector2f>(worldSize))
{
	unsigned int const numOfHerbies = 15;
	unsigned int const numOfCarnies = 5;

	for (unsigned int i = 0; i < numOfHerbies; i++)
	{
		mListOfHerbivores.push_back(new Herbivore(sf::Vector2f(myMath::randIntervalf(0, static_cast<int>(mWorldSize.x)), myMath::randIntervalf(0, static_cast<int>(mWorldSize.y)))));
	}
	for (unsigned int i = 0; i < numOfCarnies; i++)
	{
		mListOfCarnivores.push_back(new Carnivore(sf::Vector2f(myMath::randIntervalf(0, static_cast<int>(mWorldSize.x)), myMath::randIntervalf(0, static_cast<int>(mWorldSize.y)))));
	}
	for (unsigned int i = 0; i < mNumOfFood; i++)
	{
		mListOfFood.push_back(new Food(sf::Vector2f(myMath::randIntervalf(0, static_cast<int>(mWorldSize.x)), myMath::randIntervalf(0, static_cast<int>(mWorldSize.y)))));
	}
}

World::~World()
{

}

void World::update(sf::Time frametime)
{
	//Update herbies and carnies
	for (auto herb : mListOfHerbivores)
	{
		herb->update(frametime);
	}
	for (auto carn : mListOfCarnivores)
	{
		carn->update(frametime);
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


}

void World::render(sf::RenderWindow *renderWindow)
{
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
}

void World::handleEvents()
{

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
			if (mySFML::lengthOf(foodPos - herbPos) < (foodRad + herbRad))
			{
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
			if (mySFML::lengthOf(herbPos - carnPos) < (herbRad + carnRad))
			{
				herbIt = mListOfHerbivores.erase(herbIt);
				(*carnIt)->addHealth(15.f);
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
			carnIt = mListOfCarnivores.erase(carnIt);
		}
		else
		{
			++carnIt;
		}
	}
}