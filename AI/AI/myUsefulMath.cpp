#include "stdafx.h"
#include "myUsefulMath.hpp"
#include <cstdlib>

namespace myMath {

	float myMath::meanValue(float num1, float num2)
	{
		return ((num1 + num2) / 2.f);
	}


	int myMath::randIntervali(int small, int big)
	{
		return (rand() % (big - small + 1) + small);
	}

	float myMath::randIntervalf(int small, int big)
	{
		return static_cast<float>(myMath::randIntervali(small, big));
	}

	bool myMath::randBool()
	{
		return static_cast<bool>(myMath::randIntervali(0, 1));
	}

	int myMath::sign(int value)
	{
		if (value < 0)
		{
			return (-1);
		}
		else
		{
			return 1;
		}
	}

	float myMath::sign(float value)
	{
		if (value < 0)
		{
			return (-1.f);
		}
		else
		{
			return 1.f;
		}
	}

	int intPow(int val, unsigned int exp)
	{
		if (val == 0 && exp == 0)
		{
			std::cout << "Error: intPow(int, unsigned int) should calculate 0^0!" << std::endl;
			throw std::bad_exception();
			return 0;
		}
		if (val == 0)
		{
			return 0;
		}
		if (exp == 0)
		{
			return 1;
		}
		//All other cases arrive here
		int output = 1;
		for (unsigned int prodNum = 0; prodNum < exp; prodNum++)
		{
			output = output * val;
		}
		return output;
	}

	unsigned int myMath::trafoBoolVectorToUInt(std::vector<bool> input)
	{
		if (input.empty())
		{
			std::cout << "Warning: myMath::trafoBoolVectorToUInt(std::vector<bool>) : Input Vector is empty!" << std::endl;
			return 0;
		}
		unsigned int output = 0;
		unsigned int bitPos = input.size() - 1;
		unsigned int bitWeight = 1;
		bool firstIteration = true;
		while (bitPos != 0)
		{
			if (firstIteration)
			{
				firstIteration = false;
			}
			else
			{
				bitPos = bitPos - 1;
				bitWeight = bitWeight * 2;
			}
			if (input.at(bitPos))
			{
				output = output + bitWeight;
			}
		}
		return output;
	}


}