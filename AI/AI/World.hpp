#ifndef WORLD_HPP
#define WORLD_HPP


#include <iostream>
#include <list>
#include <functional>

#include "Element.hpp"
#include "Creature.hpp"
#include "Herbivore.hpp"
#include "Carnivore.hpp"
#include "Food.hpp"
#include "Window.hpp"
#include "DataListener.hpp"

#include "myUsefulMath.hpp"



class World : public Element
{
private:
	sf::Font *pFont;

	sf::RectangleShape mWorldBackground;

	std::list<Carnivore*> mListOfCarnivores;
	std::list<Herbivore*> mListOfHerbivores;
	std::list<Food*> mListOfFood;

	sf::Vector2f mWorldSize;
	sf::Time mSimulationTime;

	unsigned int const mNumOfFood = 1000;
	sf::Time mFoodSpawningTime = sf::seconds(0.02f);
	sf::Time mTimeSinceLastFoodSpawn = sf::seconds(0.f);

	DataListener mDataListener; //Hier weitermachen!!!
	unsigned int mActualNumberOfCarnies;
	unsigned int mActualNumberOfHerbies;
	unsigned int mActualNumberOfFood;


	Window *pWindow = nullptr;


public:
	World();
	World(sf::Vector2u worldSize, sf::Font* font);
	~World() override;

	void update(sf::Time frametime, sf::RenderWindow *pRenderWindow) override;
	void render(sf::RenderWindow *renderWindow) override;
	void handleEvents() override;


private:
	void calculateWhatCreaturesSee();
	void herbiesEatFood();
	void carniesEatHerbies();
	void spawnFood(sf::Time frametime);
	void creaturesDieWithoutFood();
	void creaturesReproduce();

	sf::Vector2f periodicDistance(sf::Vector2f creature1Pos, sf::Vector2f creature2Pos) const;
	bool checkForOverlap(Creature *creature1, Creature *creature2) const;
};

//Define which Brain shall be used
typedef ListBrain USED_BRAIN;




#endif //WORLD_HPP