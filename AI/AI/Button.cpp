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
	  mOutlineColorProperties(outlineColorProp),
	  mOutlineThickness(outlineThickness),
	  mButtonPressed(false)
{
	pButtonRectangle = new sf::RectangleShape;
	pButtonRectangle->setPosition(mButtonPosition);
	pButtonRectangle->setSize(mButtonSize);
	pButtonRectangle->setFillColor(mBackgroundColorProperties.normalColor);
	pButtonRectangle->setOutlineThickness(mOutlineThickness);
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
void Button::update(sf::Time frametime, sf::RenderWindow *pRenderWindow)
{
	sf::View defaultView = pRenderWindow->getDefaultView();
	sf::View actualView = pRenderWindow->getView();
	pRenderWindow->setView(defaultView);
	sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*pRenderWindow));
	pRenderWindow->setView(actualView);

	bool mousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	bool mouseOverButton = mySFML::smaller(mButtonPosition - sf::Vector2f(mOutlineThickness, mOutlineThickness), mousePosition) && mySFML::smaller(mousePosition, mButtonPosition + mButtonSize + sf::Vector2f(mOutlineThickness, mOutlineThickness));
	mButtonPressed = mousePressed && mouseOverButton;

	if (mouseOverButton)
	{
		if (mousePressed)
		{
			pButtonRectangle->setFillColor(mBackgroundColorProperties.pressedColor);
			pButtonRectangle->setOutlineColor(mOutlineColorProperties.pressedColor);
		}
		else
		{
			pButtonRectangle->setFillColor(mBackgroundColorProperties.contactColor);
			pButtonRectangle->setOutlineColor(mOutlineColorProperties.contactColor);
		}
	}
	else
	{
		pButtonRectangle->setFillColor(mBackgroundColorProperties.normalColor);
		pButtonRectangle->setOutlineColor(mOutlineColorProperties.normalColor);
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


//Setter
void Button::move(sf::Vector2f const & offset)
{
	mButtonPosition = mButtonPosition + offset;
	pButtonRectangle->move(offset);
	for (auto shape : mListOfShapes)
	{
		shape->move(offset);
	}
}


//Getter
bool Button::getButtonPressed() const
{
	return mButtonPressed;
}


//Access to mListOfDrawables
void Button::useShape(sf::Shape *shape)
{
	shape->move(mButtonPosition);
	mListOfShapes.push_back(shape);
}