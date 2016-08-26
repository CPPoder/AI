#ifndef CREATURE_HPP
#define CREATURE_HPP


#include "Element.hpp"
#include "Brain.hpp"


class Creature : public Element
{
private:
	sf::CircleShape mCircleShape;

	Brain *pBrain;
	//pBrain->calculateWantedForce(Inputs)
	//pBrain->mutate(Parameter?)
	//...

	float mMass;
	sf::Vector2f mVelocity;



public:
	Creature();
	Creature(sf::Vector2f position, sf::Color color);
	Creature(sf::Vector2f position, sf::Color color, float size);
	~Creature() override;

	void update(sf::Time frametime) override;
	void render(sf::RenderWindow *renderWindow) override;
	void handleEvents() override;

	void setPosition(sf::Vector2f position);

	sf::Vector2f getPosition() const;



};





#endif //CREATURE_HPP