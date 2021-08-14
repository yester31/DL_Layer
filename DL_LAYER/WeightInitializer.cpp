// 2021-8-14 by YH PARK
/***************************************************************************
	Weight Initializer algotirhm (Xavier, He)
****************************************************************************/
#include <random>
#include <vector>
#include <math.h>

//Xavier는 주로 Sigmoid 등 미분가능 함수에, He는 ReLU등 선형함수에 이용
enum WeightsInitMode { XavierUniformMode = 0, XavierNormalMode = 1, HeUniformMode = 2, HeNormalMode = 3 };

template<typename T>
void InitWeightsXavierUni()
{
	vector<vector<T>>& Weights
	const size_t& PrevLayerNodeNumber,
	const size_t& NextLayerNodeNumber,

	Weights.resize(PrevLayerNodeNumber + BiasNodeNumber);

	for (size_t elt = 0; elt < PrevLayerNodeNumber + BiasNodeNumber; elt++)
	{
		Weights[elt].resize(NextLayerNodeNumber);
	}

	T min = -sqrt(6 / (T)(PrevLayerNodeNumber + NextLayerNodeNumber + BiasNodeNumber));
	T max = sqrt(6 / (T)(PrevLayerNodeNumber + NextLayerNodeNumber + BiasNodeNumber));
	mt19937 random((random_device()()));
	uniform_real_distribution<T> dist(min, max);

	for (size_t elt_prev = 0; elt_prev < PrevLayerNodeNumber + BiasNodeNumber; elt_prev++)
	{
		for (size_t elt_next = 0; elt_next < NextLayerNodeNumber; elt_next++)
		{
			Weights[elt_prev][elt_next] = dist(random);
		}
	}
}

template<typename T>
void InitWeightsXavierNorm(const size_t& PrevLayerNodeNumber,
	const size_t& NextLayerNodeNumber, vector<vector<T>>& Weights)
{
	Weights.resize(PrevLayerNodeNumber + BiasNodeNumber);

	for (size_t elt = 0; elt < PrevLayerNodeNumber + BiasNodeNumber; elt++)
	{
		Weights[elt].resize(NextLayerNodeNumber);
	}

	T sigma = sqrt(2 / (T)(PrevLayerNodeNumber + NextLayerNodeNumber + BiasNodeNumber));
	random_device rd;
	mt19937 gen(rd());

	for (size_t elt_prev = 0; elt_prev < PrevLayerNodeNumber + BiasNodeNumber; elt_prev++)
	{
		for (size_t elt_next = 0; elt_next < NextLayerNodeNumber; elt_next++)
		{
			normal_distribution<T> d(0, sigma);
			Weights[elt_prev][elt_next] = d(gen);
		}
	}
}

template<typename T>
void InitWeightsHeUni(const size_t& PrevLayerNodeNumber,
	const size_t& NextLayerNodeNumber, vector<vector<T>>& Weights)
{
	Weights.resize(PrevLayerNodeNumber + BiasNodeNumber);

	for (size_t elt = 0; elt < PrevLayerNodeNumber + BiasNodeNumber; elt++)
	{
		Weights[elt].resize(NextLayerNodeNumber);
	}

	T min = -sqrt(6 / (T)(PrevLayerNodeNumber + BiasNodeNumber));
	T max = sqrt(6 / (T)(PrevLayerNodeNumber + BiasNodeNumber));
	mt19937 random((random_device()()));
	uniform_real_distribution<T> dist(min, max);

	for (size_t elt_prev = 0; elt_prev < PrevLayerNodeNumber + BiasNodeNumber; elt_prev++)
	{
		for (size_t elt_next = 0; elt_next < NextLayerNodeNumber; elt_next++)
		{
			Weights[elt_prev][elt_next] = dist(random);
		}
	}
}


template<typename T>
void InitWeightsHeNorm(const size_t& PrevLayerNodeNumber,
	const size_t& NextLayerNodeNumber, vector<vector<T>>& Weights)
{
	Weights.resize(PrevLayerNodeNumber + BiasNodeNumber);

	for (size_t elt = 0; elt < PrevLayerNodeNumber + BiasNodeNumber; elt++)
	{
		Weights[elt].resize(NextLayerNodeNumber);
	}

	T sigma = sqrt(2 / (T)PrevLayerNodeNumber + BiasNodeNumber);
	random_device rd;
	mt19937 gen(rd());

	for (size_t elt_prev = 0; elt_prev < PrevLayerNodeNumber + BiasNodeNumber; elt_prev++)
	{
		for (size_t elt_next = 0; elt_next < NextLayerNodeNumber; elt_next++)
		{
			normal_distribution<T> d(0, sigma);
			Weights[elt_prev][elt_next] = d(gen);
		}
	}
}

template<typename T>
void InitWeights(
	const size_t& PrevLayerNodeNumber, 
	const size_t& NextLayerNodeNumber,
	vector<vector<T>>& Weights, 
	WeightsInitMode WeightsMode
)
{
	switch (WeightsMode)
	{
	case XavierUniformMode:
		InitWeightsXavierUni(PrevLayerNodeNumber, NextLayerNodeNumber, Weights);
		break;

	case XavierNormalMode:
		InitWeightsXavierNorm(PrevLayerNodeNumber, NextLayerNodeNumber, Weights);
		break;

	case HeUniformMode:
		InitWeightsHeUni(PrevLayerNodeNumber, NextLayerNodeNumber, Weights);
		break;

	case HeNormalMode:
		InitWeightsHeNorm(PrevLayerNodeNumber, NextLayerNodeNumber, Weights);
		break;
	}
}