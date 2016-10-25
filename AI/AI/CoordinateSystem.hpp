#ifndef COORDINATESYSTEM_HPP
#define COORDINATESYSTEM_HPP


#include "SFML\Graphics.hpp"

#include <list>
#include <string>




class CoordinateSystem
{
private:
	sf::Vector2f mXRange;
	sf::Vector2f mYRange;
	sf::Vector2f mScreenFillFactor;
	sf::Vector2f mPlotFieldTranslation;

	std::list<sf::VertexArray> mListOfVertexArrays;
	std::list<sf::Text> mListOfTexts;


	sf::Font *pFont;
	std::string mTitle;
	std::string mXLabel;
	std::string mYLabel;
	unsigned int mCharacterSize;


public:
	CoordinateSystem(sf::Font *font);
	CoordinateSystem(sf::Vector2f xRange, sf::Vector2f yRange, sf::Vector2f screenFillFactor, sf::Vector2f plotFieldTranslation, std::string title, std::string xLabel, std::string yLabel, sf::Font *font);
	~CoordinateSystem();

	std::list<sf::VertexArray> getListOfVertexArrays() const;
	std::list<sf::Text> getListOfTexts() const;

private:
	sf::Vector2f calcPos(sf::Vector2f pos) const;
	sf::Vector2f calcSFillFactorCorrectedPos(sf::Vector2f pos) const;
};








#endif //COORDINATESYSTEM_HPP