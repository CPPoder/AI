#ifndef CARNIVORE_HPP
#define CARNIVORE_HPP


#include "Element.hpp"
#include "Creature.hpp"


class Carnivore : public Creature
{
private:



public:
	Carnivore();
	Carnivore(sf::Vector2f position, Brain *brain);
	~Carnivore() override;

	//void update() override;
	//void render(sf::RenderWindow *renderWindow) override;
	//void handleEvents() override;




};





#endif //CARNIVORE_HPP