#include "stdafx.h"
#include "Screen.hpp"


///////////
//DrawStuff

//Constructor
DrawStuff::DrawStuff()
{

}

//Detailed Construction
DrawStuff::DrawStuff(std::list<LayeredShape> const & listOfLayeredShapes, std::list<LayeredSprite> const & listOfLayeredSprites, std::list<LayeredText> const & listOfLayeredTexts)
{
	mListOfShapes = listOfLayeredShapes;
	mListOfSprites = listOfLayeredSprites;
	mListOfTexts = listOfLayeredTexts;
}

//Destructor
DrawStuff::~DrawStuff()
{

}

//Setter
void DrawStuff::clear()
{
	mListOfShapes.clear();
	mListOfSprites.clear();
	mListOfTexts.clear();
}
void DrawStuff::setListOfShapes(std::list<LayeredShape> const & listOfShapes)
{
	mListOfShapes = listOfShapes;
}
void DrawStuff::setListOfSprites(std::list<LayeredSprite> const & listOfSprites)
{
	mListOfSprites = listOfSprites;
}
void DrawStuff::setListOfTexts(std::list<LayeredText> const & listOfTexts)
{
	mListOfTexts = listOfTexts;
}
void DrawStuff::addDrawStuff(DrawStuff const & drawStuff)
{
	std::list<LayeredShape> shapeList = drawStuff.mListOfShapes;
	std::list<LayeredSprite> spriteList = drawStuff.mListOfSprites;
	std::list<LayeredText> textList = drawStuff.mListOfTexts;
	for (auto shape : shapeList)
	{
		mListOfShapes.push_back(shape);
	}
	for (auto sprite : spriteList)
	{
		mListOfSprites.push_back(sprite);
	}
	for (auto text : textList)
	{
		mListOfTexts.push_back(text);
	}
}
void DrawStuff::setDrawStuff(DrawStuff const & drawStuff)
{
	mListOfShapes = drawStuff.mListOfShapes;
	mListOfSprites = drawStuff.mListOfSprites;
	mListOfTexts = drawStuff.mListOfTexts;
}

//Getter
unsigned int DrawStuff::getGreatestLayer() const
{
	unsigned int greatestLayer = 0;
	for (auto shape : mListOfShapes)
	{
		if (shape.layer > greatestLayer)
		{
			greatestLayer = shape.layer;
		}
	}
	for (auto sprite : mListOfSprites)
	{
		if (sprite.layer > greatestLayer)
		{
			greatestLayer = sprite.layer;
		}
	}
	for (auto text : mListOfTexts)
	{
		if (text.layer > greatestLayer)
		{
			greatestLayer = text.layer;
		}
	}
	return greatestLayer;
}

//Render one Layer
void DrawStuff::render(sf::RenderWindow *pRenderWindow, unsigned int layer) const
{
	for (auto shape : mListOfShapes)
	{
		if (shape.layer == layer)
		{
			shape.render(pRenderWindow);
		}
	}
	for (auto sprite : mListOfSprites)
	{
		if (sprite.layer == layer)
		{
			sprite.render(pRenderWindow);
		}
	}
	for (auto text : mListOfTexts)
	{
		if (text.layer == layer)
		{
			text.render(pRenderWindow);
		}
	}
}





////////
//Screen

//Constructor
Screen::Screen()
	: Screen::Screen(sf::FloatRect(sf::Vector2f(), sf::Vector2f()), sf::Color::Black)
{
}
Screen::Screen(sf::FloatRect const & viewportRectangle, sf::Color backgroundColor)
	: mViewportRectangle(viewportRectangle)
{
	mBackgroundRectangleShape.setPosition(mViewportRectangle.left, mViewportRectangle.top);
	mBackgroundRectangleShape.setSize(sf::Vector2f(mViewportRectangle.width, mViewportRectangle.height));
	mBackgroundRectangleShape.setFillColor(backgroundColor);
}

//Destructor
Screen::~Screen()
{

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
	sf::View screenView = defaultView;
	sf::Vector2f defaultViewSize = defaultView.getSize();
	float leftRelWinPos = mViewportRectangle.left / defaultViewSize.x;
	float rightRelWinPos = (mViewportRectangle.left + mViewportRectangle.width) / defaultViewSize.x;
	float upperRelWinPos = mViewportRectangle.top / defaultViewSize.y;
	float lowerRelWinPos = (mViewportRectangle.top + mViewportRectangle.height) / defaultViewSize.y;
	screenView.setViewport(sf::FloatRect(sf::Vector2f(leftRelWinPos, upperRelWinPos), sf::Vector2f(rightRelWinPos - leftRelWinPos, lowerRelWinPos - upperRelWinPos)));

	//Set View
	pRenderWindow->setView(screenView);

	//Render
	pRenderWindow->draw(mBackgroundRectangleShape);
	unsigned int greatestLayer = mDrawStuff.getGreatestLayer();
	for (unsigned int layer = 0; layer <= greatestLayer; layer++)
	{
		mDrawStuff.render(pRenderWindow, layer);
	}

	//Reset View
	pRenderWindow->setView(defaultView);


}


//Setter
void Screen::clearDrawStuff()
{
	mDrawStuff.clear();
}
void Screen::addDrawStuff(DrawStuff const & drawStuff)
{
	mDrawStuff.addDrawStuff(drawStuff);
}
void Screen::setDrawStuff(DrawStuff const & drawStuff)
{
	mDrawStuff.setDrawStuff(drawStuff);
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




