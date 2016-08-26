#include "stdafx.h"
#include "World.hpp"


World::World()
	: World::World(sf::Vector2u(800, 800))
{
}

World::World(sf::Vector2u worldSize)
	: mWorldSize(static_cast<sf::Vector2f>(worldSize))
{
	unsigned int const numOfHerbies = 10;
	unsigned int const numOfCarnies = 10;

	for (unsigned int i = 0; i < numOfHerbies; i++)
	{
		mListOfHerbivores.push_back(new Herbivore(sf::Vector2f(200.f, 200.f)));
	}
	for (unsigned int i = 0; i < numOfCarnies; i++)
	{
		mListOfCarnivores.push_back(new Carnivore(sf::Vector2f(300.f, 200.f)));
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
			}
			else
			{
				++foodIt;
			}
		}
	}
}