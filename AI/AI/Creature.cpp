#include "stdafx.h"
#include "Creature.hpp"



Creature::Creature()
	: Creature::Creature(sf::Vector2f(200.f, 200.f), sf::Color::Blue, new RandomBrain)
{
}

Creature::Creature(sf::Vector2f position, sf::Color color, Brain *brain)
	: Creature::Creature(position, color, 10.f, brain)
{
}

Creature::Creature(sf::Vector2f position, sf::Color color, float size, Brain *brain)
	: mMass(1.0f),
	  mMaximalForce(1000.f),
	  mVelocity(0.f, 0.f),
	  mBarSize(30.f, 3.f),
	  mHealth(90.f),
	  mFullHealth(100.f),
	  mFertility(0.f),
	  mFullFertility(100.f),
	  mVecFromCircleToHealthBar(-15.f, -20.f),
	  mHealthBar(position + mVecFromCircleToHealthBar, mBarSize, sf::Color::Green, sf::Color::Red, (mHealth / mFullHealth)),
	  mVecFromCircleToFertilityBar(-15.f, -25.f),
	  mFertilityBar(position + mVecFromCircleToFertilityBar, mBarSize, sf::Color(0,0,255), sf::Color(125,125,255), (mFertility / mFullFertility))
{
	mCircleShape.setRadius(size);
	mCircleShape.setOrigin(size, size);
	mCircleShape.setPosition(position);
	mCircleShape.setFillColor(color);

	pBrain = brain;
}

Creature::~Creature()
{
	delete pBrain;
	pBrain = nullptr;
}


void Creature::update(sf::Time frametime, sf::RenderWindow *pRenderWindow)
{
	//Translation
	pBrain->setInputFromSence(mInputFromSence);
	sf::Vector2f wantedForce = pBrain->calculateWantedForce();
	float const viscosity = 0.005f;
	sf::Vector2f frictionForce = -6.f * 3.141592653f * viscosity * mCircleShape.getRadius() * mVelocity;
	sf::Vector2f accelaration = (wantedForce + frictionForce) / mMass;
	mVelocity = mVelocity + frametime.asSeconds() * accelaration;
	mCircleShape.move(mVelocity * frametime.asSeconds());
	mHealthBar.move(mVelocity * frametime.asSeconds());
	mFertilityBar.move(mVelocity * frametime.asSeconds());

	//Loss of Health
	float const healthLossConstant = 0.5f;
	mHealth = mHealth - (healthLossConstant * frametime.asSeconds());
	if (mHealth < 0.f)
	{
		mHealth = 0.f;
		mHasDied = true;
	}
	mHealthBar.setFillQuotient(mHealth / mFullHealth);

	//Change of Fertility depended on Health
	float const fertilityConstant = 0.1f;
	mFertility = mFertility + (fertilityConstant * (mHealth - 80.f) * frametime.asSeconds());
	if (mFertility < 0.f) mFertility = 0.f;
	if (mFertility > mFullFertility) mFertility = mFullFertility;
	mFertilityBar.setFillQuotient(mFertility / mFullFertility);
	if (mFertility > 95.f)
	{
		mAbleToReproduce = true;
	}
	else
	{
		mAbleToReproduce = false;
	}
}

void Creature::render(sf::RenderWindow *renderWindow)
{
	renderWindow->draw(mCircleShape);
	mHealthBar.render(renderWindow);
	mFertilityBar.render(renderWindow);
}

void Creature::handleEvents()
{
}


void Creature::setPosition(sf::Vector2f position)
{
	mCircleShape.setPosition(position);
	mHealthBar.setPosition(position + mVecFromCircleToHealthBar);
	mFertilityBar.setPosition(position + mVecFromCircleToFertilityBar);
}
void Creature::addHealth(float health)
{
	mHealth = mHealth + health;
	if (mHealth > 100.f)
	{
		mHealth = 100.f;
	}
	mHealthBar.setFillQuotient(mHealth / mFullHealth);
}
void Creature::resetFertility()
{
	mFertility = 0.f;
	mAbleToReproduce = false;
	mFertilityBar.setFillQuotient(0.f);
}
void Creature::setInputFromSence(std::vector<bool> inputFromSence)
{
	mInputFromSence = inputFromSence;
}


sf::Vector2f Creature::getPosition() const
{
	return mCircleShape.getPosition();
}
float Creature::getRadius() const
{
	return mCircleShape.getRadius();
}
bool Creature::getHasDied() const
{
	return mHasDied;
}
bool Creature::getAbleToReproduce() const
{
	return mAbleToReproduce;
}
Brain* Creature::getBrainPointer() const
{
	return pBrain;
}