#ifndef DATAPRESENTER_HPP
#define DATAPRESENTER_HPP

#include "SFML\Graphics.hpp"
#include <list>

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



	


public:
	DataPresenter(sf::Font *font);
	~DataPresenter();

	std::list<sf::VertexArray> getListOfVertexArrays() const;
	std::list<sf::Text> getListOfTexts() const;


};






#endif //DATAPRESENTER_HPP