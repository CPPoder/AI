#include "stdafx.h"
#include "mySFMLVectorFunctions.hpp"
#include "myUsefulMath.hpp"

namespace mySFML {

	sf::Vector2f mySFML::meanVector(sf::Vector2f vec1, sf::Vector2f vec2)
	{
		return sf::Vector2f(myMath::meanValue(vec1.x, vec2.x), myMath::meanValue(vec1.y, vec2.y));
	}

	sf::Vector2f mySFML::createNormalVectorWithAngle(float angleInRadiant)
	{
		return sf::Vector2f(cos(angleInRadiant), sin(angleInRadiant));
	}

	sf::Vector2f mySFML::dirtyRandNormalVector(int parameter)
	{
		//return mySFML::normalize(sf::Vector2f(static_cast<float>(rand()), static_cast<float>(rand())));
		return mySFML::normalize(sf::Vector2f(myMath::randIntervalf(-parameter, parameter),myMath::randIntervalf(-parameter, parameter)));
	}

	bool mySFML::smaller(sf::Vector2f smallerVector, sf::Vector2f largerVector)
	{
		bool xSmaller = (smallerVector.x < largerVector.x);
		bool ySmaller = (smallerVector.y < largerVector.y);

		return (xSmaller && ySmaller);
	}
	bool mySFML::smaller(sf::Vector2f smallerVector, sf::Vector2f largerVector, bool &xSmaller, bool &ySmaller)
	{
		xSmaller = (smallerVector.x < largerVector.x);
		ySmaller = (smallerVector.y < largerVector.y);

		return ( xSmaller && ySmaller);
	}

	bool mySFML::smaller(sf::Vector2i smallerVector, sf::Vector2i largerVector)
	{
		bool xSmaller = (smallerVector.x < largerVector.x);
		bool ySmaller = (smallerVector.y < largerVector.y);

		return (xSmaller && ySmaller);
	}
	bool mySFML::smaller(sf::Vector2i smallerVector, sf::Vector2i largerVector, bool &xSmaller, bool &ySmaller)
	{
		xSmaller = (smallerVector.x < largerVector.x);
		ySmaller = (smallerVector.y < largerVector.y);

		return (xSmaller && ySmaller);
	}

	sf::Color mySFML::colorMultiplication(sf::Color color, float factor)
	{
		return sf::Color(color.r * factor, color.g * factor, color.b * factor);
	}

	sf::Color mySFML::mixColors(sf::Color color1, sf::Color color2, float weight1, float weight2)
	{
		return (colorMultiplication(color1, weight1) + colorMultiplication(color2, weight2));
	}

	sf::RectangleShape mySFML::createRectangleShape(sf::Vector2f const & pos, sf::Vector2f const & size, float rotation, sf::Color const & fillColor, float outlineThickness, sf::Color const & outlineColor)
	{
		sf::RectangleShape shape;
		shape.setPosition(pos);
		shape.setSize(size);
		shape.rotate(rotation);
		shape.setFillColor(fillColor);
		shape.setOutlineColor(outlineColor);
		shape.setOutlineThickness(outlineThickness);
		return shape;
	}
	
}