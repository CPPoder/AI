#ifndef HERBIVORE_HPP
#define HERBIVORE_HPP


#include "Element.hpp"
#include "Creature.hpp"


class Herbivore : public Creature
{
private:



public:
	Herbivore();
	Herbivore(sf::Vector2f position, Brain *brain);
	~Herbivore() override;

	//void update() override;
	//void render(sf::RenderWindow *renderWindow) override;
	//void handleEvents() override;




};





#endif //HERBIVORE_HPP