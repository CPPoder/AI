#include "stdafx.h"
#include "DataPresenter.hpp"



DataPresenter::DataPresenter(sf::Font *font)
	: pFont(font),
	  mXRange(-10.f, 10.f),
	  mYRange(-10.f, 10.f),
	  mScreenFillFactor(0.8f, 0.8f),
	  mPlotFieldTranslation(0.02f, 0.0f),
	  mCoordinateSystem(mXRange, mYRange, mScreenFillFactor, mPlotFieldTranslation, "Creature Evolution over Time", "Time in s", "Number of Creatures", pFont),
	  mDataPresenterChanged(true),
	  mCoordinateSystemLayer(0)
{
}

DataPresenter::~DataPresenter()
{
}





void DataPresenter::update()
{

}





std::list<std::pair<sf::VertexArray, unsigned int>> DataPresenter::getListOfVertexArrays() const
{
	std::list<sf::VertexArray> coordinateSystemVertexArrayList = mCoordinateSystem.getListOfVertexArrays();
	//Use now all vertex arrays! Not only from coordinate system!
	std::list<std::pair<sf::VertexArray, unsigned int>> fullVertexArrayList;
	for (auto vertexArray : coordinateSystemVertexArrayList)
	{
		fullVertexArrayList.push_back(std::pair<sf::VertexArray, unsigned int>(vertexArray, mCoordinateSystemLayer));
	}
	return fullVertexArrayList;
}

std::list<std::pair<sf::Text, unsigned int>> DataPresenter::getListOfTexts() const
{
	std::list<sf::Text> coordinateSystemTextList = mCoordinateSystem.getListOfTexts();
	//Use now all texts! Not only from coordinate system!
	std::list<std::pair<sf::Text, unsigned int>> fullTextList;
	for (auto text : coordinateSystemTextList)
	{
		fullTextList.push_back(std::pair<sf::Text, unsigned int>(text, mCoordinateSystemLayer));
	}
	return fullTextList;
}

bool DataPresenter::getHasChanged() const
{
	std::cout << mDataPresenterChanged << std::endl;
	return mDataPresenterChanged;
}




void DataPresenter::usedAllNewData()
{
	mDataPresenterChanged = false;
}


