#ifndef FOOD_HPP
#define FOOD_HPP

#include "Element.hpp"



class Food : public Element
{
private:
	sf::CircleShape mCircleShape;


public:
	Food();
	Food(sf::Vector2f position);
	~Food() override;

	void update(sf::Time frametime) override;
	void render(sf::RenderWindow *renderWindow) override;
	void handleEvents() override;

	void setPosition(sf::Vector2f position);

	sf::Vector2f getPosition() const;
	float getRadius() const;
};




#endif //FOOD_HPP