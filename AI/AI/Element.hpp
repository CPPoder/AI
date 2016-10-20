#ifndef ELEMENT_HPP
#define ELEMENT_HPP


#include <iostream>

#include "SFML\Graphics.hpp"



class Element
{
private:


public:
    Element();
    virtual ~Element();

	virtual void handleEvents() = 0;
	virtual void update(sf::Time frametime, sf::RenderWindow *pRenderWindow) = 0;
	virtual void render(sf::RenderWindow *pRenderWindow) = 0;

};




#endif
