#ifndef CREATURE_HPP
#define CREATURE_HPP


#include "Element.hpp"
#include "Brain.hpp"
#include "Bar.hpp"

#include <vector>


class Creature : public Element
{
private:
	Brain *pBrain;

	float mMass;
	float mMaximalForce;
	sf::Vector2f mVelocity;

	float const mFullHealth;
	float mHealth;

	float const mFullFertility;
	float mFertility; //Ability of Reproduction
	bool mAbleToReproduce = false;

	bool mHasDied = false;


	sf::CircleShape mCircleShape;

	sf::Vector2f mBarSize;

	sf::Vector2f mVecFromCircleToHealthBar;
	Bar mHealthBar;

	sf::Vector2f mVecFromCircleToFertilityBar;
	Bar mFertilityBar;

	std::vector<bool> mInputFromSence;



public:
	Creature();
	Creature(sf::Vector2f position, sf::Color color, Brain *brain);
	Creature(sf::Vector2f position, sf::Color color, float size, Brain *brain);
	~Creature() override;

	void update(sf::Time frametime, sf::RenderWindow *pRenderWindow) override;
	void render(sf::RenderWindow *renderWindow) override;
	void handleEvents() override;

	void setPosition(sf::Vector2f position);
	void addHealth(float health);
	void resetFertility();
	void setInputFromSence(std::vector<bool> inputFromSence);

	sf::Vector2f getPosition() const;
	float getRadius() const;
	bool getHasDied() const;
	bool getAbleToReproduce() const;
	Brain* getBrainPointer() const;



};





#endif //CREATURE_HPP