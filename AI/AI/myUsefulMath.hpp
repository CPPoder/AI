#ifndef MYUSEFULMATH_HPP
#define MYUSEFULMATH_HPP

#include <vector>
#include <iostream>
#include <functional>

namespace myMath {

	template <typename T> T max(T num1, T num2)
	{
		if (num1 > num2)
		{
			return num1;
		}
		else
		{
			return num2;
		}
	}

	template <typename T> T min(T num1, T num2)
	{
		if (num1 > num2)
		{
			return num2;
		}
		else
		{
			return num1;
		}
	}

	float meanValue(float num1, float num2);

	int randIntervali(int small, int big);

	float randIntervalf(int small, int big);

	bool randBool();

	template <typename T> T abs(T value)
	{
		if (value < T(0))
		{
			return (-value);
		}
		else
		{
			return value;
		}
	}

	int sign(int value);
	float sign(float value);

	int intPow(int val, unsigned int exp);

	unsigned int trafoBoolVectorToUInt(std::vector<bool> input);
	std::vector<bool> trafoUintToBoolVector(unsigned int input);
	std::vector<bool> trafoUintToBoolVectorOfGivenSize(unsigned int input, unsigned int size);

	
	template <typename T, typename S> S intervalBasedAffineTrafo(T domainBegin, T domainEnd, S imageBegin, S imageEnd, T input)
	{
		//Cast to S
		S dB = static_cast<S>(domainBegin);
		S dE = static_cast<S>(domainEnd);
		S iB = imageBegin;
		S iE = imageEnd;
		S in = static_cast<S>(input);
		
		//Check for empty Intervals
		if ((iB == iE) || (dB == dE))
		{
			std::cout << "Error: S myMath::intervalBasedAffineTrafo(T, T, S, S) : Domain or Image are empty!" << std::endl;
			throw std::bad_exception();
			return S(0);
		}

		//Calculate Transformation Parameters
		S m = (iE - iB) / (dE - dB);
		S t = iB - (m * dB);

		//Perform Transformation
		return ((m * in) + t);
	}
	
	template <typename T, typename S> std::function<S(T)> createIntervalBasedAffineTrafo(T domainBegin, T domainEnd, S imageBegin, S imageEnd)
	{
		//Cast to S
		S dB = static_cast<S>(domainBegin);
		S dE = static_cast<S>(domainEnd);
		S iB = imageBegin;
		S iE = imageEnd;

		//Check for empty Intervals
		if ((iB == iE) || (dB == dE))
		{
			std::cout << "Error: S myMath::intervalBasedAffineTrafo(T, T, S, S) : Domain or Image are empty!" << std::endl;
			throw std::bad_exception();
			return std::function<S(T)>();
		}

		//Calculate Transformation Parameters
		S m = (iE - iB) / (dE - dB);
		S t = iB - (m * dB);

		//Return Function
		std::function<S(T)> trafo = [=](T input) {
			S in = static_cast<S>(input);
			return ((m * in) + t);
		};
		return trafo;
	}
	
}



#endif