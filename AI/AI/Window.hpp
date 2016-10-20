#ifndef WINDOW_HPP
#define WINDOW_HPP


#include "Element.hpp"
#include "Button.hpp"

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




public:
	Window(sf::Font *font);
	~Window() override;

	void handleEvents() override;
	void update(sf::Time frametime) override;
	void render(sf::RenderWindow *pRenderWindow) override;


};










#endif //WINDOW_HPP