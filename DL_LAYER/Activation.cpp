// 2021-8-03 by YH PARK // 검증 필요

/***************************************************************************
	Activateion function algotirhm (Tanh, ReLU, Sigmoid)
****************************************************************************/
#include "Utils.h"

enum act_func{Linear, Sigmoid, Tanh, ReLU, Swish, LeakRelu};

template <typename T>
T act_Sigmoid(T x) {
	return (1.f / (exp(-x) + 1.f));
}

template <typename T>
T act_Tanh(T x) {
	return tanh(x);
}

template <typename T>
T act_ReLU(T x) {
	return (x >= 0 ? x : 0);
}

template <typename T>
T act_Swish(T x) {
	return (x * act_Sigmoid(x));
}

template <typename T>
T act_ReakyRelu(T x, T a = 0.01) {
	return (x >= 0 ? x : a * x);
}

template <typename T>
const T ActivationMode(const T x, act_func Mode, const T a)
{
	switch (Mode)
	{
	case Linear:
		return x;

	case Sigmoid:
		return act_Sigmoid(x);

	case Tanh:
		return act_Tanh(x);

	case ReLU:
		return act_ReLU(x);

	case Swish:
		return act_Swish(x);

	case LeakRelu:
		return act_ReakyRelu(x, a);
	}
}

template <typename T>
void activation(vector<T>& Output, vector<T>& Input, act_func mode = Linear, const T a = 0.01) {
	cout << "===== activation ===== \n";
	Output.resize(Input.size());

	for (int i = 0; i < Input.size(); i++)
	{
		Output[i] = ActivationMode(Input[i], mode, a);
	}
}

int main() 
{
	vector<float> input(10);
	vector<float> output(10);

	initTensor(input);

	activation(output, input, act_func::Sigmoid);

	valueCheck(output);


	return 0;
}