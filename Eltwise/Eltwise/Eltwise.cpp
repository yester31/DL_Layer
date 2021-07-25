// 2021/07/25 by yhpark

/***************************************************************************
	Pooling algotirhm (avg & max)
****************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <cassert>
using namespace std;
using namespace chrono;

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

void valueCheck(vector<float>& Input, int IN, int IC, int IH, int IW, bool one = false) {
	std::cout << "===== valueCheck func =====" << std::endl;
	if (one) IN = 1;
	int N_offset = IC * IH * IW;
	int C_offset, H_offset, W_offset, g_idx;
	for (int ⁠n_idx = 0; ⁠n_idx < IN; ⁠n_idx++) {
		C_offset = ⁠n_idx * N_offset;
		for (int ⁠c_idx = 0; ⁠c_idx < IC; ⁠c_idx++) {
			H_offset = ⁠c_idx * IW * IH + C_offset;
			for (int ⁠h_idx = 0; ⁠h_idx < IH; ⁠h_idx++) {
				W_offset = ⁠h_idx * IW + H_offset;
				for (int w_idx = 0; w_idx < IW; w_idx++) {
					g_idx = w_idx + W_offset;
					std::cout << setw(5) << Input[g_idx] << " ";
				}std::cout << std::endl;
			}std::cout << std::endl; std::cout << std::endl;
		}
	}
}

void InitTensor(vector<float>& container, float start = 1.f, float step = 0)
{
	std::cout << "===== InitTensor func =====" << std::endl;
	float count = start;
	for (int i = 0; i < container.size(); i++) {
		container[i] = count;
		count += step;
	}
}

void tofile(vector<float> &Buffer, string fname = "../../output/C_Tensor") {
	std::ofstream fs(fname, ios::binary);
	if (fs.is_open())
		fs.write((const char*)Buffer.data(), Buffer.size() * sizeof(float));
	fs.close();
	std::cout << "the output file produced in output folder." << std::endl;
}


int main()
{
	int IN = 2;
	int IC = 2;
	int IH = 4;
	int IW = 4;

	// d[IN][IC][IH][IW] 
	// 임시 input 값 
	vector<float> input1(IN * IC * IH * IW);
	InitTensor(input1, 1);
	valueCheck(input1, IN, IC, IH, IW);

	vector<float> input2(IN * IC * IH * IW);
	InitTensor(input2, 2);
	valueCheck(input2, IN, IC, IH, IW);

	vector<float> output(IN * IC * IH * IW);
	valueCheck(output, IN, IC, IH, IW);

	long long start_usec = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();

	//eltwiseSum(output, input1, input2);
	eltwiseProd(output, input1, input2);

	long long end_usec = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
	int frame_sec = int(end_usec - start_usec);

	valueCheck(output, IN, IC, IH, IW);


	std::cout << "======================================================" << std::endl;
	std::cout << "dur time :: " << frame_sec << " [micro sec]" << std::endl;

	tofile(output, "../../output/C_Tensor_elt");
}
