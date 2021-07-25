// 2021-7-24 by YH PARK

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
using namespace std;
using namespace chrono;


void avgPooling(vector<float>& avgPoolingOutput, vector<float>& avgPoolingInput, int input_n, int input_c, int input_h, int input_w, int poolingWindow, int poolingStride, int poolingOutputHeight, int poolingOutputWidth) {
	//cout << "===== AvgPooling ===== \n";	
	//avgPoolingOutput.resize(input_n*input_c*poolingOutputHeight*poolingOutputWidth);
	float poolingWindowAreaInverse = 1.f / (poolingWindow * poolingWindow);
	int temp1i = input_h * input_w * input_c;
	int temp1o = poolingOutputHeight * poolingOutputWidth * input_c;
	for (int ⁠n_idx = 0; ⁠n_idx < input_n; ⁠n_idx++)
	{
		int temp2i = ⁠n_idx * temp1i;
		int temp2o = ⁠n_idx * temp1o;
		for (int ⁠c_idx = 0; ⁠c_idx < input_c; ⁠c_idx++)
		{
			int temp3i = ⁠c_idx * input_w * input_h + temp2i;
			int temp3o = ⁠c_idx * poolingOutputHeight * poolingOutputWidth + temp2o;
			for (int rowStride = 0; rowStride < poolingOutputHeight; rowStride++) {
				int temp4o = rowStride * poolingOutputWidth + temp3o;
				for (int colStride = 0; colStride < poolingOutputWidth; colStride++) {
					float sum = 0;
					int g_idx_o = colStride + temp4o;
					for (int x = rowStride * poolingStride; x < rowStride * poolingStride + poolingWindow; x++) {
						int temp4i = x * input_w + temp3i;
						for (int y = colStride * poolingStride; y < colStride * poolingStride + poolingWindow; y++) {
							int ⁠g_idx_i = y + temp4i;
							sum += avgPoolingInput[⁠g_idx_i];
						}
					}
					avgPoolingOutput[g_idx_o] = sum * poolingWindowAreaInverse;
				}
			}
		}
	}
}

void maxPooling(vector<float>& maxPoolingOutput, vector<float>& maxPoolingInput, int input_n, int input_c, int input_h, int input_w, int poolingWindow, int poolingStride, int poolingOutputHeight, int poolingOutputWidth) {
	cout << "===== maxPooling ===== \n";

	int temp1i = input_h * input_w * input_c;
	int temp1o = poolingOutputHeight * poolingOutputWidth * input_c;
	for (int ⁠n_idx = 0; ⁠n_idx < input_n; ⁠n_idx++)
	{
		int temp2i = ⁠n_idx * temp1i;
		int temp2o = ⁠n_idx * temp1o;
		for (int ⁠c_idx = 0; ⁠c_idx < input_c; ⁠c_idx++)
		{
			int temp3i = ⁠c_idx * input_w * input_h + temp2i;
			int temp3o = ⁠c_idx * poolingOutputHeight * poolingOutputWidth + temp2o;
			for (int rowStride = 0; rowStride < poolingOutputHeight; rowStride++)
			{
				int temp4o = rowStride * poolingOutputWidth + temp3o;
				for (int colStride = 0; colStride < poolingOutputWidth; colStride++)
				{
					float maxValue = 0;
					int g_idx_o = colStride + temp4o;
					for (int x = rowStride * poolingStride; x < rowStride * poolingStride + poolingWindow; x++)
					{
						int temp4i = x * input_w + temp3i;
						for (int y = colStride * poolingStride; y < colStride * poolingStride + poolingWindow; y++)
						{
							int ⁠g_idx_i = y + temp4i;
							if (maxValue < maxPoolingInput[⁠g_idx_i])
							{
								maxValue = maxPoolingInput[⁠g_idx_i];
							}
						}
					}
					maxPoolingOutput[g_idx_o] = maxValue;
				}
			}
		}
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

void scalarTensor(vector<float>& output, int OC, int IC, int KH, int KW, float start = 1.f, int step = 0) {
	std::cout << "===== scalarTensor func =====" << std::endl;
	std::cout << "Tensor[" << OC << "][" << IC << "][" << KH << "][" << KW << "]" << std::endl << std::endl;
	int N_offset = IC * KH * KW;
	int C_offset, H_offset, W_offset, g_idx;
	for (int ⁠n_idx = 0; ⁠n_idx < OC; ⁠n_idx++) {
		C_offset = ⁠n_idx * N_offset;
		for (int ⁠c_idx = 0; ⁠c_idx < IC; ⁠c_idx++) {
			H_offset = ⁠c_idx * KH * KW + C_offset;
			for (int ⁠h_idx = 0; ⁠h_idx < KH; ⁠h_idx++) {
				W_offset = ⁠h_idx * KW + H_offset;
				for (int w_idx = 0; w_idx < KW; w_idx++) {
					g_idx = w_idx + W_offset;
					start += step;
					output[g_idx] = start;
				}
			}
		}
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
	vector<float> input(IN * IC * IH * IW);
	scalarTensor(input, IN, IC, IH, IW, 0, 1);
	valueCheck(input, IN, IC, IH, IW, 1);

	int poolingWindow = 3;
	int poolingStride = 1;
	int poolingOutputHeight = ((IH - poolingWindow) / poolingStride) + 1;
	int poolingOutputWidth = ((IW - poolingWindow) / poolingStride) + 1;
	int poolingOutputSize = IN * IC * poolingOutputHeight * poolingOutputWidth;
	vector<float> poolingOutput(poolingOutputSize);

	long long start_usec = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();

	maxPooling(poolingOutput, input, IN, IC, IH, IW, poolingWindow, poolingStride, poolingOutputHeight, poolingOutputWidth);
	//avgPooling(poolingOutput, input, IN, IC, IH, IW, poolingWindow, poolingStride, poolingOutputHeight, poolingOutputWidth);

	long long end_usec = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
	int frame_sec = int(end_usec - start_usec);

	valueCheck(poolingOutput, IN, IC, poolingOutputHeight, poolingOutputWidth, 1);

	std::cout << "======================================================" << std::endl;
	std::cout << "dur time :: " << frame_sec << " [micro sec]" << std::endl;

	tofile(poolingOutput, "../../output/C_Tensor_max_p");	// max pooling 사용시
	//tofile(poolingOutput, "../../output/C_Tensor_avg_p"); // avg pooling 사용시

}

