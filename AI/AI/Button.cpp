#include "stdafx.h"
#include "Button.hpp"

///////////////////////
//ButtonColorProperties

ButtonColorProperties::ButtonColorProperties()
	: ButtonColorProperties::ButtonColorProperties(sf::Color::Black)
{
}

ButtonColorProperties::ButtonColorProperties(sf::Color allColors)
	: ButtonColorProperties::ButtonColorProperties(allColors, allColors, allColors)
{
}

ButtonColorProperties::ButtonColorProperties(sf::Color _normalColor, sf::Color _contactColor, sf::Color _pressedColor)
	: normalColor(_normalColor),
	contactColor(_contactColor),
	pressedColor(_pressedColor)
{
}

ButtonColorProperties const ButtonColorProperties::CloseButtonBackgroundColorProperties = ButtonColorProperties(sf::Color::Red, sf::Color(150, 0, 0), sf::Color(100, 0, 0));
ButtonColorProperties const ButtonColorProperties::CloseButtonOutlineColorProperties = ButtonColorProperties(sf::Color::Black, sf::Color::Black, sf::Color(50, 50, 50));








////////
//Button


//Constructor
Button::Button(sf::Vector2f buttonPos, sf::Vector2f buttonSize, ButtonColorProperties backgroundColorProp, float outlineThickness, ButtonColorProperties outlineColorProp)
	: mButtonPosition(buttonPos),
	  mButtonSize(buttonSize),
	  mBackgroundColorProperties(backgroundColorProp),
	  mOutlineColorProperties(outlineColorProp)
{
	pButtonRectangle = new sf::RectangleShape;
	pButtonRectangle->setPosition(mButtonPosition);
	pButtonRectangle->setSize(mButtonSize);
	pButtonRectangle->setFillColor(mBackgroundColorProperties.normalColor);
	pButtonRectangle->setOutlineThickness(outlineThickness);
	pButtonRectangle->setOutlineColor(mOutlineColorProperties.normalColor);
}

//Destructor
Button::~Button()
{
	delete pButtonRectangle;
	pButtonRectangle = nullptr;

	for (auto shape : mListOfShapes)
	{
		delete shape;
		shape = nullptr;
	}
}


//Handle Events
void Button::handleEvents()
{

}

//Update
void Button::update(sf::Time frametime)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if (buttonWasUnpressed)
		{
			buttonWasUnpressed = false;
			switch (helper)
			{
			case 1:
				helper = 2;
				pButtonRectangle->setFillColor(mBackgroundColorProperties.contactColor);
				pButtonRectangle->setOutlineColor(mOutlineColorProperties.contactColor);
				break;
			case 2:
				helper = 3;
				pButtonRectangle->setFillColor(mBackgroundColorProperties.pressedColor);
				pButtonRectangle->setOutlineColor(mOutlineColorProperties.pressedColor);
				break;
			case 3:
				helper = 1;
				pButtonRectangle->setFillColor(mBackgroundColorProperties.normalColor);
				pButtonRectangle->setOutlineColor(mOutlineColorProperties.normalColor);
				break;
			}
		}
	}
	else
	{
		buttonWasUnpressed = true;
	}
}

//Render
void Button::render(sf::RenderWindow *pRenderWindow)
{
	pRenderWindow->draw(*pButtonRectangle);
	for (auto shape : mListOfShapes)
	{
		pRenderWindow->draw(*shape);
	}
}




//Access to mListOfDrawables
void Button::useShape(sf::Shape *shape)
{
	shape->move(mButtonPosition);
	mListOfShapes.push_back(shape);
}


