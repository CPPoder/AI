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
	  mCharacterSize(16),
	  mXTickNumber(11),
	  mYTickNumber(11),
	  mTickLength(0.02f)
{
	//Frame
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

	//Ticks
	unsigned int totalTickNumber = (2 * mXTickNumber + 2 * mYTickNumber);
	sf::VertexArray tics(sf::Lines, 2*totalTickNumber);
	for (unsigned int i = 0; i < 2*totalTickNumber; i++) //Color
	{
		tics[i].color = sf::Color::Black;
	}
	std::function<sf::Vector2f(unsigned int, unsigned int, bool, bool, bool)> GetXTicksPosition = [this](unsigned int actTickNum, unsigned int fullTickNum, bool lowerPoint, bool lowerTicks, bool xTicks)
	{
		sf::Vector2f out;
		if (xTicks)
		{
			out.x = static_cast<float>(actTickNum) / static_cast<float>(fullTickNum - 1);
			if (lowerTicks)
			{
				out.y = 1.f;
			}
			else
			{
				out.y = 0.f;
			}
			if (lowerPoint)
			{
				out.y = out.y + mTickLength / 2.f;
			}
			else
			{
				out.y = out.y - mTickLength / 2.f;
			}
		}
		else
		{
			out.y = static_cast<float>(actTickNum) / static_cast<float>(fullTickNum - 1);
			if (lowerTicks)
			{
				out.x = 1.f;
			}
			else
			{
				out.x = 0.f;
			}
			if (lowerPoint)
			{
				out.x = out.x + mTickLength / 2.f;
			}
			else
			{
				out.x = out.x - mTickLength / 2.f;
			}
		}
		return out;
	};
	for (unsigned int i = 0; i < 2*mXTickNumber; i = i + 2) //Lower xTicks
	{
		tics[i].position = calcSFillFactorCorrectedPos(GetXTicksPosition(i/2, mXTickNumber, true, true, true));
		tics[i+1].position = calcSFillFactorCorrectedPos(GetXTicksPosition(i/2, mXTickNumber, false, true, true));
	}
	for (unsigned int i = 0; i < 2*mXTickNumber; i = i + 2) //Higher xTicks
	{
		tics[i + 2 * mXTickNumber].position = calcSFillFactorCorrectedPos(GetXTicksPosition(i/2, mXTickNumber, true, false, true));
		tics[i + 1 + 2 * mXTickNumber].position = calcSFillFactorCorrectedPos(GetXTicksPosition(i/2, mXTickNumber, false, false, true));
	}
	for (unsigned int i = 0; i < 2*mXTickNumber; i = i + 2) //Lower yTicks
	{
		tics[i + 4 * mXTickNumber].position = calcSFillFactorCorrectedPos(GetXTicksPosition(i/2, mYTickNumber, true, true, false));
		tics[i + 1 + 4 * mXTickNumber].position = calcSFillFactorCorrectedPos(GetXTicksPosition(i/2, mYTickNumber, false, true, false));
	}
	for (unsigned int i = 0; i < 2*mXTickNumber; i = i + 2) //Higher yTicks
	{
		tics[i + 2 * mYTickNumber + 4 * mXTickNumber].position = calcSFillFactorCorrectedPos(GetXTicksPosition(i/2, mYTickNumber, true, false, false));
		tics[i + 1 + 2 * mYTickNumber + 4 * mXTickNumber].position = calcSFillFactorCorrectedPos(GetXTicksPosition(i/2, mYTickNumber, false, false, false));
	}
	mListOfVertexArrays.push_back(tics);

	//Title
	sf::Text titleText(mTitle, *pFont, mCharacterSize);
	titleText.setStyle(sf::Text::Bold);
	titleText.setColor(sf::Color::Black);
	titleText.setOrigin(titleText.getLocalBounds().width / 2.f, titleText.getLocalBounds().height / 2.f);
	titleText.setPosition(calcSFillFactorCorrectedPos(sf::Vector2f(0.5f, -0.05f)));
	mListOfTexts.push_back(titleText);

	//XLabel
	sf::Text xLabelText(mXLabel, *pFont, mCharacterSize);
	xLabelText.setColor(sf::Color::Black);
	xLabelText.setOrigin(xLabelText.getLocalBounds().width / 2.f, xLabelText.getLocalBounds().height / 2.f);
	xLabelText.setPosition(calcSFillFactorCorrectedPos(sf::Vector2f(0.5f, 1.05f)));
	mListOfTexts.push_back(xLabelText);

	//YLabel
	sf::Text yLabelText(mYLabel, *pFont, mCharacterSize);
	yLabelText.setColor(sf::Color::Black);
	yLabelText.setOrigin(yLabelText.getLocalBounds().width / 2.f, yLabelText.getLocalBounds().height / 2.f);
	yLabelText.rotate(90.f);
	yLabelText.setPosition(calcSFillFactorCorrectedPos(sf::Vector2f(-0.05f, 0.5f)));
	mListOfTexts.push_back(yLabelText);
}


CoordinateSystem::~CoordinateSystem()
{

}


//Getter
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

//Setter
void CoordinateSystem::setXRange(float low, float high)
{
	mXRange = sf::Vector2f(low, high);
}
void CoordinateSystem::setYRange(float low, float high)
{
	mYRange = sf::Vector2f(low, high);
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