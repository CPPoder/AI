#ifndef WINDOW_HPP
#define WINDOW_HPP


#include "Element.hpp"
#include "Button.hpp"
#include "Screen.hpp"

#include "SFML\Graphics.hpp"



class Window : public Element
{
private:
	sf::Vector2f mPosition;
	sf::Vector2f mWindowSize;
	float mTitleBarHeight;
	float mRimThickness;

	sf::RectangleShape *pBackgroundRectangle;
	sf::RectangleShape *pTitleBarRectangle;
	sf::RectangleShape *pRimRectangle;

	sf::Font *pFont;
	sf::Text *pTitleText;

	Button *pCloseButton;
	float mCloseButtonOutlineThickness;
	sf::Vector2f mCloseButtonSize;
	sf::Vector2f mRelCloseButtonPos;

	bool mMovable;
	bool mResizable;
	sf::Vector2f lastMousePosition;

	bool mCloseButtonWasPressed;
	bool mCloseButtonReleased;

	Screen *pScreen;



public:
	Window(sf::Font *font);
	~Window() override;

	void handleEvents() override;
	void update(sf::Time frametime, sf::RenderWindow *pRenderWindow) override;
	void render(sf::RenderWindow *pRenderWindow) override;

	void move(sf::Vector2f const & offset);
	void resizeWindow(sf::Vector2f const & offset);

	bool getCloseButtonReleased() const;

	void clearDrawStuff();
	void addShape(sf::Shape *shapePointer, unsigned int layer);
	void addSprite(sf::Sprite *spritePointer, unsigned int layer);
	void addText(sf::Text *textPointer, unsigned int layer);
	void addVertexArray(sf::VertexArray *vertexArrayPointer, unsigned int layer);
	void setScreenBackgroundColor(sf::Color backgroundColor);

	//Screen* getScreenPointer() const;

	

};










#endif //WINDOW_HPP