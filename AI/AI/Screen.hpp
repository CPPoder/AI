#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "Element.hpp"

#include "SFML\Graphics.hpp"

#include <list>


/////////////////////////////
//Enum: LayeredDrawObjectType
enum class LayeredDrawObjectType
{
	Shape,
	Sprite,
	Text
};




///////////////////////////
//Class: LayeredDrawObjects
template <typename T> class LayeredDrawObject
{
public:
	//Public Variables
	T *drawObject;
	unsigned int layer;


	//Constructors
private:
	LayeredDrawObject() = delete;

public:
	LayeredDrawObject(T *_drawObject)
		: LayeredDrawObject::LayeredDrawObject(_drawObject, 0)
	{
	}

	LayeredDrawObject(T *_drawObject, unsigned int _layer)
		: drawObject(_drawObject),
		  layer(_layer)
	{
	}


	//Destructor
	~LayeredDrawObject()
	{
		delete drawObject;
		drawObject = nullptr;
	}

	//Render
	void render(sf::RenderWindow *pRenderWindow) const
	{
		pRenderWindow->draw(*drawObject);
	}

};

typedef LayeredDrawObject<sf::Shape>  LayeredShape;
typedef LayeredDrawObject<sf::Sprite> LayeredSprite;
typedef LayeredDrawObject<sf::Text>   LayeredText;




///////////////////
//Class: Draw Stuff
class DrawStuff
{
private:
	//Private Class Members
	std::list<LayeredShape> mListOfShapes;
	std::list<LayeredSprite> mListOfSprites;
	std::list<LayeredText> mListOfTexts;

public:
	//Constructors & Destructor
	DrawStuff();

	template <typename T> DrawStuff(std::list<T> const & listOfLayeredDrawObjects, LayeredDrawObjectType type)
		: DrawStuff::DrawStuff()
	{
		DrawStuff::setListOfDrawObjects(listOfLayeredDrawObjects, type);
	}

	DrawStuff(std::list<LayeredShape> const & listOfLayeredShapes, std::list<LayeredSprite> const & listOfLayeredSprites, std::list<LayeredText> const & listOfLayeredTexts);
	
	~DrawStuff();

	//Setter
	void clear();
	void setListOfShapes(std::list<LayeredShape> const & listOfShapes);
	void setListOfSprites(std::list<LayeredSprite> const & listOfSprites);
	void setListOfTexts(std::list<LayeredText> const & listOfTexts);
	void addDrawStuff(DrawStuff const & drawStuff);
	void setDrawStuff(DrawStuff const & drawStuff);
	template <typename T> void setListOfDrawObjects(std::list<T> const & listOfDrawObjects, LayeredDrawObjectType type)
	{
		switch (type)
		{
		case Shape:
			mListOfShapes = listOfLayeredDrawObjects;
			break;
		case Sprite:
			mListOfSprites = listOfLayeredDrawObjects;
			break;
		case Text:
			mListOfTexts = listOfLayeredDrawObjects;
			break;
		}
	}
	
	template <typename T> void push_back(T const & layeredDrawObject, LayeredDrawObjectType type)
	{
		switch (type)
		{
		case Shape:
			mListOfShapes.push_back(layeredDrawObjects);
			break;
		case Sprite:
			mListOfSprites.push_back(layeredDrawObjects);
			break;
		case Text:
			mListOfTexts.push_back(layeredDrawObjects);
			break;
		}
	}

	//Getter
	unsigned int getGreatestLayer() const;

	//Render one Layer
	void render(sf::RenderWindow *pRenderWindow, unsigned int layer) const;

};




///////////////
//Class: Screen
class Screen : public Element
{
private:
	DrawStuff mDrawStuff;
	sf::FloatRect mViewportRectangle;
	sf::RectangleShape mBackgroundRectangleShape;

public:
	Screen();
	Screen(sf::FloatRect const & viewportRectangle, sf::Color backgroundColor);
	~Screen() override;

	void handleEvents() override;
	void update(sf::Time frametime, sf::RenderWindow *pRenderWindow) override;
	void render(sf::RenderWindow *pRenderWindow) override;

	void clearDrawStuff();
	void addDrawStuff(DrawStuff const & drawStuff);
	void setDrawStuff(DrawStuff const & drawStuff);
	void setViewport(sf::FloatRect viewportRectangle);
	void moveViewport(sf::Vector2f offset);
	void setViewportSize(sf::Vector2f size);
	void changeViewportSize(sf::Vector2f offset);
	void setBackgroundColor(sf::Color backgroundColor);

};





#endif //SCREEN_HPP