#pragma once
#include <random>

class Random
{
private:
	static std::mt19937 gen;

public:
	Random()
	{
		std::random_device rd;
		gen.seed(rd());
	}

	~Random()
	{
	}

	template<typename T>
	static T DiscreteRange(T min, T max)
	{
		std::uniform_int_distribution<T> dis(min, max);
		return dis(gen);
	}

	template<typename T>
	static T RealRange(T min, T max)
	{
		std::uniform_real_distribution<T> dis(min, max);
		return dis(gen);
	}
};

inline std::mt19937 Random::gen;
