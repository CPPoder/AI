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
}

void World::render(sf::RenderWindow *renderWindow)
{
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