#include "stdafx.h"
#include "CoordinateSystem.hpp"



CoordinateSystem::CoordinateSystem(sf::Font *font)
	: CoordinateSystem::CoordinateSystem(sf::Vector2f(-10.f, 10.f), sf::Vector2f(-10.f, 10.f), sf::Vector2f(0.8f, 0.8f), sf::Vector2f(0.f, 0.f), "", "", "", font)
{
}


CoordinateSystem::CoordinateSystem(sf::Vector2f xRange, sf::Vector2f yRange, sf::Vector2f screenFillFactor, sf::Vector2f plotFieldTranslation, std::string title, std::string xLabel, std::string yLabel, sf::Font *font)
	: pFont(font),
	  mXRange(xRange),
	  mYRange(yRange),
	  mScreenFillFactor(screenFillFactor),
	  mPlotFieldTranslation(plotFieldTranslation),
	  mTitle(title),
	  mXLabel(xLabel),
	  mYLabel(yLabel),
	  mCharacterSize(15)
{
	sf::VertexArray frame(sf::LinesStrip, 5);
	for (unsigned int i = 0; i < 5; i++)
	{
	frame[i].color = sf::Color::Black;
	}
	frame[0].position = calcSFillFactorCorrectedPos(sf::Vector2f(0.f, 0.f));
	frame[1].position = calcSFillFactorCorrectedPos(sf::Vector2f(1.f, 0.f));
	frame[2].position = calcSFillFactorCorrectedPos(sf::Vector2f(1.f, 1.f));
	frame[3].position = calcSFillFactorCorrectedPos(sf::Vector2f(0.f, 1.f));
	frame[4].position = calcSFillFactorCorrectedPos(sf::Vector2f(0.f, 0.f));
	mListOfVertexArrays.push_back(frame);


	sf::Text titleText(mTitle, *pFont, mCharacterSize);
	titleText.setColor(sf::Color::Black);
	titleText.setOrigin(titleText.getLocalBounds().width / 2.f, titleText.getLocalBounds().height / 2.f);
	titleText.setPosition(sf::Vector2f(0.5f, 0.05f));
	mListOfTexts.push_back(titleText);
}


CoordinateSystem::~CoordinateSystem()
{

}



std::list<sf::VertexArray> CoordinateSystem::getListOfVertexArrays() const
{
	std::list<sf::VertexArray> list;
	for (auto vertexArray : mListOfVertexArrays)
	{
		list.push_back(vertexArray);
	}
	return list;
}

std::list<sf::Text> CoordinateSystem::getListOfTexts() const
{
	return mListOfTexts;
}




sf::Vector2f CoordinateSystem::calcPos(sf::Vector2f pos) const
{
	return sf::Vector2f();
}


sf::Vector2f CoordinateSystem::calcSFillFactorCorrectedPos(sf::Vector2f pos) const
{
	sf::Vector2f corrPos;
	corrPos.x = 0.5f + mScreenFillFactor.x * (pos.x - 0.5f);
	corrPos.y = 0.5f + mScreenFillFactor.y * (pos.y - 0.5f);
	return (corrPos + mPlotFieldTranslation);
}