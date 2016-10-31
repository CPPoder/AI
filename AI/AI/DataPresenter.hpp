#ifndef DATAPRESENTER_HPP
#define DATAPRESENTER_HPP

#include "SFML\Graphics.hpp"

#include <list>
#include <iostream>

#include "CoordinateSystem.hpp"



class DataPresenter
{
private:
	sf::Font *pFont;

	sf::Vector2f mXRange;
	sf::Vector2f mYRange;
	sf::Vector2f mScreenFillFactor;
	sf::Vector2f mPlotFieldTranslation;

	CoordinateSystem mCoordinateSystem;
	unsigned int mCoordinateSystemLayer;

	bool mDataPresenterChanged;



	


public:
	DataPresenter(sf::Font *font);
	~DataPresenter();

	void update();

	std::list<std::pair<sf::VertexArray, unsigned int>> getListOfVertexArrays() const;
	std::list<std::pair<sf::Text, unsigned int>> getListOfTexts() const;
	bool getHasChanged() const;

	void usedAllNewData();


};






#endif //DATAPRESENTER_HPP