#ifndef BUTTON_HPP
#define BUTTON_HPP


#include "Element.hpp"

#include "SFML\Graphics.hpp"

#include <list>


class ButtonColorProperties
{
public:
	sf::Color normalColor;
	sf::Color contactColor;
	sf::Color pressedColor;

	ButtonColorProperties();
	explicit ButtonColorProperties(sf::Color allColors);
	ButtonColorProperties(sf::Color _normalColor, sf::Color _contactColor, sf::Color _pressedColor);

	static const ButtonColorProperties CloseButtonBackgroundColorProperties;
	static const ButtonColorProperties CloseButtonOutlineColorProperties;
};








class Button : public Element
{
private:
	sf::Vector2f mButtonPosition;
	sf::Vector2f mButtonSize;

	ButtonColorProperties mBackgroundColorProperties;
	ButtonColorProperties mOutlineColorProperties;

	sf::RectangleShape *pButtonRectangle;
	std::list<sf::Shape*> mListOfShapes;

	int helper = 1;
	bool buttonWasUnpressed = true;


public:
	Button(sf::Vector2f buttonPos, sf::Vector2f buttonSize, ButtonColorProperties backgroundColorProp, float outlineThickness, ButtonColorProperties outlineColorProp);
	~Button() override;

	void handleEvents() override;
	void update(sf::Time frametime) override;
	void render(sf::RenderWindow *pRenderWindow) override;

	void useShape(sf::Shape *shape);


};





#endif //BUTTON_HPP