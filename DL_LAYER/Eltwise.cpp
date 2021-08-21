// 2021/07/25 by yhpark

/***************************************************************************
	Pooling algotirhm (avg & max)
****************************************************************************/
#include "Tensor.h"

void eltwiseSum(vector<float>& output, vector<float>& input1, vector<float>& input2)
{
	std::cout << "===== eltwiseSum func =====" << std::endl;
	assert(input1.size() == input2.size());
	assert(input1.size() == output.size());

	for (int i = 0; i < output.size(); i++) {
		output[i] = input1[i] + input2[i];
	}
}

void eltwiseProd(vector<float>& output, vector<float>& input1, vector<float>& input2)
{
	std::cout << "===== eltwiseProd func =====" << std::endl;
	assert(input1.size() == input2.size());
	assert(input1.size() == output.size());

	for (int i = 0; i < output.size(); i++) {
		output[i] = input1[i] * input2[i];
	}
}



//int main()
//{
//	int IN = 2;
//	int IC = 2;
//	int IH = 4;
//	int IW = 4;
//
//	// d[IN][IC][IH][IW] 
//	// 임시 input 값 
//	vector<float> input1(IN * IC * IH * IW);
//	initTensor(input1, 1);
//	valueCheck(input1, IN, IC, IH, IW);
//
//	vector<float> input2(IN * IC * IH * IW);
//	initTensor(input2, 2);
//	valueCheck(input2, IN, IC, IH, IW);
//
//	vector<float> output(IN * IC * IH * IW);
//	valueCheck(output, IN, IC, IH, IW);
//
//	long long start_usec = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
//
//	//eltwiseSum(output, input1, input2);
//	eltwiseProd(output, input1, input2);
//
//	long long end_usec = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
//	int frame_sec = int(end_usec - start_usec);
//
//	valueCheck(output, IN, IC, IH, IW);
//
//
//	std::cout << "======================================================" << std::endl;
//	std::cout << "dur time :: " << frame_sec << " [micro sec]" << std::endl;
//
//	tofile(output, "../Calc_Validation/output/C_Tensor_elt");
//}
