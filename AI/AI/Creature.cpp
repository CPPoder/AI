#include "stdafx.h"
#include "Creature.hpp"



Creature::Creature()
	: Creature::Creature(sf::Vector2f(200.f, 200.f), sf::Color::Blue)
{
}

Creature::Creature(sf::Vector2f position, sf::Color color)
	: Creature::Creature(position, color, 10.f)
{
}

Creature::Creature(sf::Vector2f position, sf::Color color, float size)
	: mMass(1.0f),
	  mVelocity(0.f, 0.f)
{
	mCircleShape.setRadius(size);
	mCircleShape.setOrigin(size, size);
	mCircleShape.setPosition(position);
	mCircleShape.setFillColor(color);
	

	pBrain = new Brain;
}

Creature::~Creature()
{
	delete pBrain;
	pBrain = nullptr;
}


void Creature::update(sf::Time frametime)
{
	//Translation
	sf::Vector2f wantedForce = pBrain->calculateWantedForce();
	float const viscosity = 0.001f;
	sf::Vector2f frictionForce = -6.f * 3.141592653f * viscosity * mCircleShape.getRadius() * mVelocity;
	sf::Vector2f accelaration = (wantedForce + frictionForce) / mMass;
	mVelocity = mVelocity + frametime.asSeconds() * accelaration;
	mCircleShape.move(mVelocity * frametime.asSeconds());

	//Loss of Health
	float const healthLossConstant = 0.5f;
	mHealth = mHealth - (healthLossConstant * frametime.asSeconds());
	if (mHealth < 0.f)
	{
		mHealth = 0.f;
		mHasDied = true;
	}
	std::cout << mHealth << std::endl;
}

void Creature::render(sf::RenderWindow *renderWindow)
{
	renderWindow->draw(mCircleShape);
}

void Creature::handleEvents()
{

}


void Creature::setPosition(sf::Vector2f position)
{
	mCircleShape.setPosition(position);
}
void Creature::addHealth(float health)
{
	mHealth = mHealth + health;
	if (mHealth > 100.f)
	{
		mHealth = 100.f;
	}
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