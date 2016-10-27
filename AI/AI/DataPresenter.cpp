#include "stdafx.h"
#include "DataPresenter.hpp"



DataPresenter::DataPresenter(sf::Font *font)
	: pFont(font),
	  mXRange(-10.f, 10.f),
	  mYRange(-10.f, 10.f),
	  mScreenFillFactor(0.8f, 0.8f),
	  mPlotFieldTranslation(0.02f, 0.0f),
	  mCoordinateSystem(mXRange, mYRange, mScreenFillFactor, mPlotFieldTranslation, "Creature Evolution over Time", "Time in s", "Number of Creatures", pFont),
	  mDataPresenterChanged(true)
{
}

DataPresenter::~DataPresenter()
{
}





void DataPresenter::update()
{

}





std::list<sf::VertexArray> DataPresenter::getListOfVertexArrays() const
{
	std::list<sf::VertexArray> coordinateSystemVertexArrayList = mCoordinateSystem.getListOfVertexArrays();
	//Use now all vertex arrays! Not only from coordinate system!
	std::list<sf::VertexArray> fullVertexArrayList = coordinateSystemVertexArrayList;
	return fullVertexArrayList;
}

std::list<sf::Text> DataPresenter::getListOfTexts() const
{
	return mCoordinateSystem.getListOfTexts();
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


