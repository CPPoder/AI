#ifndef DATAPRESENTER_HPP
#define DATAPRESENTER_HPP

#include "myUsefulMath.hpp"
#include "mySFMLVectorFunctions.hpp"

#include "SFML\Graphics.hpp"

#include <list>
#include <iostream>

#include "CoordinateSystem.hpp"
#include "DataListener.hpp"

class DataListener;

class DataPresenter
{
private:
	sf::Font *pFont;

	DataListener *pDataListener;

	sf::Vector2f mXRange;
	sf::Vector2f mYRange;
	sf::Vector2f mScreenFillFactor;
	sf::Vector2f mPlotFieldTranslation;

	CoordinateSystem mCoordinateSystem;
	unsigned int mCoordinateSystemLayer;

	std::list<std::pair<sf::VertexArray, unsigned int>> mListOfVertexArrays;

	bool mDataPresenterChanged;



	


public:
	DataPresenter(sf::Font *font, DataListener *dataListener);
	~DataPresenter();

	void update();

	std::list<std::pair<sf::VertexArray, unsigned int>> getListOfVertexArrays() const;
	std::list<std::pair<sf::Text, unsigned int>> getListOfTexts() const;
	bool getHasChanged() const;

	void usedAllNewData();


private:
	sf::Vector2f calcSFillFactorCorrectedPos(sf::Vector2f pos) const;
	sf::Vector2f calcRelPosOnScreen(sf::Vector2f absPos);


};






#endif //DATAPRESENTER_HPP

