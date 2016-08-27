#ifndef CREATURE_HPP
#define CREATURE_HPP


#include "Element.hpp"
#include "Brain.hpp"


class Creature : public Element
{
private:
	sf::CircleShape mCircleShape;

	sf::RectangleShape mHealthBar;
	sf::Vector2f mVecFromCircleToHealthBar = sf::Vector2f(-15.f, -20.f);
	sf::Vector2f mSizeOfFullHealthBar = sf::Vector2f(30.f, 3.f);
	sf::RectangleShape mLostHealthBar;

	Brain *pBrain;

	float mMass;
	sf::Vector2f mVelocity;

	float const mFullHealth = 100.f;
	float mHealth = 90.f;
	float mFertility = 0.f; //Ability of Reproduction
	bool mAbleToReproduce = false;

	bool mHasDied = false;



public:
	Creature();
	Creature(sf::Vector2f position, sf::Color color);
	Creature(sf::Vector2f position, sf::Color color, float size);
	~Creature() override;

	void update(sf::Time frametime) override;
	void render(sf::RenderWindow *renderWindow) override;
	void handleEvents() override;

	void setPosition(sf::Vector2f position);
	void addHealth(float health);

	sf::Vector2f getPosition() const;
	float getRadius() const;
	bool getHasDied() const;



};





#endif //CREATURE_HPP