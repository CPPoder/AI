#include "stdafx.h"
#include "Screen.hpp"



////////
//Screen

//Constructor
Screen::Screen()
	: Screen::Screen(sf::FloatRect(sf::Vector2f(), sf::Vector2f()), sf::Color::Black)
{
}
Screen::Screen(sf::FloatRect const & viewportRectangle, sf::Color backgroundColor)
	: mViewportRectangle(viewportRectangle),
	  mHighestLayer(0)
{
	mBackgroundRectangleShape.setPosition(0.f, 0.f);
	mBackgroundRectangleShape.setSize(sf::Vector2f(1.f, 1.f));
	mBackgroundRectangleShape.setFillColor(backgroundColor);
}

//Destructor
Screen::~Screen()
{
	Screen::deleteDrawStuff();
}


//Handle Events
void Screen::handleEvents()
{

}

//Update
void Screen::update(sf::Time frametime, sf::RenderWindow *pRenderWindow)
{

}

//Render
void Screen::render(sf::RenderWindow *pRenderWindow)
{
	//Determine Default View
	sf::View defaultView = pRenderWindow->getDefaultView();
	sf::View actualView = pRenderWindow->getView();
	sf::View screenView(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	sf::Vector2f defaultViewSize = defaultView.getSize();
	//std::cout << defaultViewSize.x << '\t' << defaultViewSize.y << std::endl;
	float leftRelWinPos = mViewportRectangle.left / defaultViewSize.x;
	float rightRelWinPos = (mViewportRectangle.left + mViewportRectangle.width) / defaultViewSize.x;
	float upperRelWinPos = mViewportRectangle.top / defaultViewSize.y;
	float lowerRelWinPos = (mViewportRectangle.top + mViewportRectangle.height) / defaultViewSize.y;
	screenView.setViewport(sf::FloatRect(sf::Vector2f(leftRelWinPos, upperRelWinPos), sf::Vector2f(rightRelWinPos - leftRelWinPos, lowerRelWinPos - upperRelWinPos)));

	//Set View
	pRenderWindow->setView(screenView);

	//Render
	pRenderWindow->draw(mBackgroundRectangleShape);
	for (unsigned int layer = 0; layer <= mHighestLayer; layer++)
	{
		Screen::renderDrawStuffLayer(pRenderWindow, layer);
	}

	//Reset View
	pRenderWindow->setView(defaultView);


}


//Setter
void Screen::clearDrawStuff()
{
	Screen::deleteDrawStuff();
	mListOfLayeredShapes.clear();
	mListOfLayeredSprites.clear();
	mListOfLayeredTexts.clear();
	mListOfLayeredVertexArrays.clear();
	mHighestLayer = 0;
}
void Screen::addShape(sf::Shape *shapePointer, unsigned int layer)
{
	mListOfLayeredShapes.push_back(std::pair<sf::Shape *, unsigned int>(shapePointer, layer));
	mHighestLayer = myMath::max(mHighestLayer, layer);
}
void Screen::addSprite(sf::Sprite *spritePointer, unsigned int layer)
{
	mListOfLayeredSprites.push_back(std::pair<sf::Sprite *, unsigned int>(spritePointer, layer));
	mHighestLayer = myMath::max(mHighestLayer, layer);
}
void Screen::addText(sf::Text *textPointer, unsigned int layer)
{
	//textPointer->setScale(0.001f, 0.001f);
	textPointer->setScale(1.f / mViewportRectangle.width, 1.f / mViewportRectangle.height);
	mListOfLayeredTexts.push_back(std::pair<sf::Text *, unsigned int>(textPointer, layer));
	mHighestLayer = myMath::max(mHighestLayer, layer);
}
void Screen::addVertexArray(sf::VertexArray *vertexArrayPointer, unsigned int layer)
{
	mListOfLayeredVertexArrays.push_back(std::pair<sf::VertexArray *, unsigned int>(vertexArrayPointer, layer));
	mHighestLayer = myMath::max(mHighestLayer, layer);
}
void Screen::setViewport(sf::FloatRect viewportRectangle)
{
	mViewportRectangle = viewportRectangle;
}
void Screen::moveViewport(sf::Vector2f offset)
{
	mViewportRectangle.left = mViewportRectangle.left + offset.x;
	mViewportRectangle.top = mViewportRectangle.top + offset.y;
}
void Screen::setViewportSize(sf::Vector2f size)
{
	mViewportRectangle.width = size.x;
	mViewportRectangle.height = size.y;
}
void Screen::changeViewportSize(sf::Vector2f offset)
{
	Screen::setViewportSize(sf::Vector2f(mViewportRectangle.width, mViewportRectangle.height) + offset);
}
void Screen::setBackgroundColor(sf::Color backgroundColor)
{
	mBackgroundRectangleShape.setFillColor(backgroundColor);
}




//Delete Draw Stuff
void Screen::deleteDrawStuff()
{
	for (auto shapePair : mListOfLayeredShapes)
	{
		delete shapePair.first;
		shapePair.first = nullptr;
	}
	for (auto spritePair : mListOfLayeredSprites)
	{
		delete spritePair.first;
		spritePair.first = nullptr;
	}
	for (auto textPair : mListOfLayeredTexts)
	{
		delete textPair.first;
		textPair.first = nullptr;
	}
	for (auto vertexArrayPair : mListOfLayeredVertexArrays)
	{
		delete vertexArrayPair.first;
		vertexArrayPair.first = nullptr;
	}
}



//Render Draw Stuff
void Screen::renderDrawStuffLayer(sf::RenderWindow *pRenderWindow, unsigned int layer)
{
	for (auto vertexArray : mListOfLayeredVertexArrays)
	{
		if (vertexArray.second == layer)
		{
			pRenderWindow->draw(*vertexArray.first);
		}
	}
	for (auto shape : mListOfLayeredShapes)
	{
		if (shape.second == layer)
		{
			pRenderWindow->draw(*shape.first);
		}
	}
	for (auto sprite : mListOfLayeredSprites)
	{
		if (sprite.second == layer)
		{
			pRenderWindow->draw(*sprite.first);
		}
	}
	for (auto text : mListOfLayeredTexts)
	{
		if (text.second == layer)
		{
			pRenderWindow->draw(*text.first);
		}
	}
}