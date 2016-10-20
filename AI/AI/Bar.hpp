#ifndef BAR_HPP
#define BAR_HPP


#include "SFML\Graphics.hpp"

#include "Element.hpp"



class Bar : public Element
{
private:
	sf::RectangleShape mBar;
	sf::RectangleShape mLostBar;

	sf::Color mBarColor;
	sf::Color mLostBarColor;

	sf::Vector2f mPosition;
	sf::Vector2f mSizeOfFullBar;

	float mFillQuotient;




public:
	Bar();
	Bar(sf::Vector2f position, sf::Vector2f fullBarSize, sf::Color barColor, sf::Color lostBarColor, float fillQuotient);
	~Bar();

	void update(sf::Time frametime, sf::RenderWindow *pRenderWindow) override;
	void render(sf::RenderWindow *renderWindow) override;
	void handleEvents() override;

	void setFillQuotient(float fillQuotient);
	void setPosition(sf::Vector2f position);
	void move(sf::Vector2f translation);

	float getFillQuotient() const;


private:
	void refresh();



};





#endif //BAR_HPP