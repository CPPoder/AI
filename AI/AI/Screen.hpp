#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "Element.hpp"

#include "SFML\Graphics.hpp"

#include "myUsefulMath.hpp"

#include <list>
#include <utility>


///////////////
//Class: Screen
class Screen : public Element
{
private:
	std::list<std::pair<sf::Shape*, unsigned int>> mListOfLayeredShapes;
	std::list<std::pair<sf::Sprite*, unsigned int>> mListOfLayeredSprites;
	std::list<std::pair<sf::Text*, unsigned int>> mListOfLayeredTexts;
	std::list<std::pair<sf::VertexArray*, unsigned int>> mListOfLayeredVertexArrays;

	unsigned int mHighestLayer;

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
	void addShape(sf::Shape *shapePointer, unsigned int layer);
	void addSprite(sf::Sprite *spritePointer, unsigned int layer);
	void addText(sf::Text *textPointer, unsigned int layer);
	void addVertexArray(sf::VertexArray *vertexArrayPointer, unsigned int layer);
	void setViewport(sf::FloatRect viewportRectangle);
	void moveViewport(sf::Vector2f offset);
	void setViewportSize(sf::Vector2f size);
	void changeViewportSize(sf::Vector2f offset);
	void setBackgroundColor(sf::Color backgroundColor);

private:
	void deleteDrawStuff();
	void renderDrawStuffLayer(sf::RenderWindow *pRenderWindow, unsigned int layer);
	inline void refreshTextScales();

};





#endif //SCREEN_HPP