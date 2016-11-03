#include "stdafx.h"
#include "DataPresenter.hpp"



DataPresenter::DataPresenter(sf::Font *font, DataListener *dataListener)
	: pFont(font),
	  pDataListener(dataListener),
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
	//Check if something must be changed. If yes, set mDataPresenterChanged true!
	if (pDataListener->mNewData)
	{
		//Determine Ranges
		auto dataVectorPointer = &pDataListener->mVecOf_Time_CreatureNumb_Pairs;
		sf::Time maxTime;
		unsigned int maxFoodNum = 0;
		unsigned int maxHerbNum = 0;
		unsigned int maxCarnNum = 0;
		for (auto data : *dataVectorPointer)
		{
			maxTime = myMath::max(maxTime, data.first);
			maxFoodNum = myMath::max(maxFoodNum, data.second.z);
			maxHerbNum = myMath::max(maxHerbNum, data.second.y);
			maxCarnNum = myMath::max(maxCarnNum, data.second.x);
		}
		mXRange = sf::Vector2f(0.f, maxTime.asSeconds());
		mYRange = sf::Vector2f(0.f, static_cast<unsigned int>(myMath::max(myMath::max(maxFoodNum, maxHerbNum), maxCarnNum)));
		mCoordinateSystem.setXRange(mXRange);
		mCoordinateSystem.setYRange(mYRange);
		mCoordinateSystem.refresh();

		float foodScale = 1.f;
		float herbScale = 4.f;
		float carnScale = 15.f;

		//Set Drawing Stuff
		mListOfVertexArrays.clear();
		{ //Food
			unsigned int const foodLayer = 2; //Food
			sf::Color const foodColor = sf::Color(200, 125, 0);
			sf::VertexArray vertexArrayFood(sf::PrimitiveType::LinesStrip, dataVectorPointer->size());
			unsigned int vertexNum = 0;
			for (auto data : *dataVectorPointer)
			{
				sf::Vector2f position = DataPresenter::calcSFillFactorCorrectedPos(DataPresenter::calcRelPosOnScreen(sf::Vector2f(data.first.asSeconds(), static_cast<float>(data.second.z*foodScale))));
				vertexArrayFood[vertexNum].color = foodColor;
				vertexArrayFood[vertexNum].position = position;
				vertexNum++;
			}
			mListOfVertexArrays.push_back(std::pair<sf::VertexArray, unsigned int>(vertexArrayFood, foodLayer));
		}
		{ //Herbies
			unsigned int const herbLayer = 2; //Herbies
			sf::Color const herbColor = sf::Color::Green;
			sf::VertexArray vertexArrayHerb(sf::PrimitiveType::LinesStrip, dataVectorPointer->size());
			unsigned int vertexNum = 0;
			for (auto data : *dataVectorPointer)
			{
				sf::Vector2f position = DataPresenter::calcSFillFactorCorrectedPos(DataPresenter::calcRelPosOnScreen(sf::Vector2f(data.first.asSeconds(), static_cast<float>(data.second.y*herbScale))));
				vertexArrayHerb[vertexNum].color = herbColor;
				vertexArrayHerb[vertexNum].position = position;
				vertexNum++;
			}
			mListOfVertexArrays.push_back(std::pair<sf::VertexArray, unsigned int>(vertexArrayHerb, herbLayer));
		}
		{ //Carnies
			unsigned int const carnLayer = 2;
			sf::Color const carnColor = sf::Color::Red;
			sf::VertexArray vertexArrayCarn(sf::PrimitiveType::LinesStrip, dataVectorPointer->size());
			unsigned int vertexNum = 0;
			for (auto data : *dataVectorPointer)
			{
				sf::Vector2f position = DataPresenter::calcSFillFactorCorrectedPos(DataPresenter::calcRelPosOnScreen(sf::Vector2f(data.first.asSeconds(), static_cast<float>(data.second.x*carnScale))));
				vertexArrayCarn[vertexNum].color = carnColor;
				vertexArrayCarn[vertexNum].position = position;
				vertexNum++;
			}
			mListOfVertexArrays.push_back(std::pair<sf::VertexArray, unsigned int>(vertexArrayCarn, carnLayer));
		}


		//Set Refreshing Variables
		pDataListener->mNewData = false;
		mDataPresenterChanged = true;
	}
}





std::list<std::pair<sf::VertexArray, unsigned int>> DataPresenter::getListOfVertexArrays() const
{
	std::list<sf::VertexArray> coordinateSystemVertexArrayList = mCoordinateSystem.getListOfVertexArrays();
	std::list<std::pair<sf::VertexArray, unsigned int>> fullVertexArrayList;
	for (auto vertexArray : coordinateSystemVertexArrayList)
	{
		fullVertexArrayList.push_back(std::pair<sf::VertexArray, unsigned int>(vertexArray, mCoordinateSystemLayer));
	}
	for (auto layeredVertexArray : mListOfVertexArrays)
	{
		fullVertexArrayList.push_back(layeredVertexArray);
	}
	return fullVertexArrayList;
}

std::list<std::pair<sf::Text, unsigned int>> DataPresenter::getListOfTexts() const
{
	std::list<sf::Text> coordinateSystemTextList = mCoordinateSystem.getListOfTexts();
	std::list<std::pair<sf::Text, unsigned int>> fullTextList;
	for (auto text : coordinateSystemTextList)
	{
		fullTextList.push_back(std::pair<sf::Text, unsigned int>(text, mCoordinateSystemLayer));
	}
	return fullTextList;
}

bool DataPresenter::getHasChanged() const
{
	//std::cout << mDataPresenterChanged << std::endl;
	return mDataPresenterChanged;
}




void DataPresenter::usedAllNewData()
{
	mDataPresenterChanged = false;
}




sf::Vector2f DataPresenter::calcSFillFactorCorrectedPos(sf::Vector2f pos) const
{
	sf::Vector2f corrPos;
	corrPos.x = 0.5f + mScreenFillFactor.x * (pos.x - 0.5f);
	corrPos.y = 0.5f + mScreenFillFactor.y * (pos.y - 0.5f);
	return (corrPos + mPlotFieldTranslation);
}


sf::Vector2f DataPresenter::calcRelPosOnScreen(sf::Vector2f absPos)
{
	sf::Vector2f out;
	out.x = myMath::intervalBasedAffineTrafo(mXRange.x, mXRange.y, 0.f, 1.f, absPos.x);
	out.y = myMath::intervalBasedAffineTrafo(mYRange.x, mYRange.y, 1.f, 0.f, absPos.y);
	return out;
}
