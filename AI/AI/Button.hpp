#ifndef BUTTON_HPP
#define BUTTON_HPP


#include "Element.hpp"

#include "mySFMLVectorFunctions.hpp"

#include "SFML\Graphics.hpp"
#include "myUsefulMath.hpp"

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
	float mOutlineThickness;

	ButtonColorProperties mBackgroundColorProperties;
	ButtonColorProperties mOutlineColorProperties;

	sf::RectangleShape *pButtonRectangle;
	std::list<sf::Shape*> mListOfShapes;

	bool mButtonPressed;


public:
	Button(sf::Vector2f buttonPos, sf::Vector2f buttonSize, ButtonColorProperties backgroundColorProp, float outlineThickness, ButtonColorProperties outlineColorProp);
	~Button() override;

	void handleEvents() override;
	void update(sf::Time frametime, sf::RenderWindow *pRenderWindow) override;
	void render(sf::RenderWindow *pRenderWindow) override;

	void move(sf::Vector2f const & offset);

	void useShape(sf::Shape *shape);

	bool getButtonPressed() const;

	
};





#endif //BUTTON_HPP