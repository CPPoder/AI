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

#include "myUsefulMath.hpp"



class World : public Element
{
private:
	std::list<Carnivore*> mListOfCarnivores;
	std::list<Herbivore*> mListOfHerbivores;
	std::list<Food*> mListOfFood;

	sf::Vector2f mWorldSize;

	unsigned int const mNumOfFood = 40;


public:
	World();
	World(sf::Vector2u worldSize);
	~World() override;

	void update(sf::Time frametime) override;
	void render(sf::RenderWindow *renderWindow) override;
	void handleEvents() override;

	void herbiesEatFood();
};




#endif //WORLD_HPP