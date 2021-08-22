// 2021-8-22 by YH PARK

/***************************************************************************
	Conventional Convolution algotirhm (without any option)
****************************************************************************/
#include "Tensor.h"

void Concat(vector<float>& Output, vector<float>& Input1, vector<float>& Input2, int IN1 = 1, int IN2 = 1, int IC = 1, int IH = 1, int IW = 1) {
	std::cout << "===== Concat func =====" << std::endl;

	int N_offset = IC * IH * IW;
	int C_offset, H_offset, W_offset, g_idx;
	int C_offset2, H_offset2, W_offset2, g_idx2;

	for (int n_idx = 0; n_idx < IN1 + IN2; n_idx++) {
		C_offset = n_idx * N_offset;
		if (n_idx < IN1)
		{
			for (int ⁠c_idx = 0; ⁠c_idx < IC; ⁠c_idx++) {
				H_offset = ⁠c_idx * IW * IH + C_offset;
				for (int ⁠h_idx = 0; ⁠h_idx < IH; ⁠h_idx++) {
					W_offset = ⁠h_idx * IW + H_offset;
					for (int w_idx = 0; w_idx < IW; w_idx++) {
						g_idx = w_idx + W_offset;
						Output[g_idx] = Input1[g_idx];
					}
				}
			}
		}
		else {
			C_offset2 = (n_idx - IN1) * N_offset;
			for (int ⁠c_idx = 0; ⁠c_idx < IC; ⁠c_idx++) {
				H_offset = ⁠c_idx * IW * IH + C_offset;
				H_offset2 = ⁠c_idx * IW * IH + C_offset2;
				for (int ⁠h_idx = 0; ⁠h_idx < IH; ⁠h_idx++) {
					W_offset = ⁠h_idx * IW + H_offset;
					W_offset2 = ⁠h_idx * IW + H_offset2;
					for (int w_idx = 0; w_idx < IW; w_idx++) {
						g_idx = w_idx + W_offset;
						g_idx2 = w_idx + W_offset2;
						Output[g_idx] = Input2[g_idx2];
					}
				}
			}	
		}
	}
}


int main()
{
	int IN1 = 2;
	int IN2 = 2;
	int IC = 2;
	int IH = 4;
	int IW = 4;
	int ON = IN1 + IN2;

	// input1[IN1][IC][IH][IW] 
	vector<float> input1(IN1 * IC * IH * IW);
	scalarTensor_b(input1, IN1, IC, IH, IW, 0, 1);
	valueCheck_b(input1, IN1, IC, IH, IW);

	// input1[IN2][IC][IH][IW] 
	vector<float> input2(IN2 * IC * IH * IW);
	scalarTensor_b(input2, IN2, IC, IH, IW, 0, 2);
	valueCheck_b(input2, IN2, IC, IH, IW);

	vector<float> output(ON * IC * IH * IW);

	long long start_usec3 = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();

	Concat(output, input1, input2, IN1, IN2, IC, IH, IW);
	valueCheck_b(output, ON, IC, IH, IW);

	long long end_usec3 = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
	int frame_sec3 = int(end_usec3 - start_usec3);

	std::cout << "======================================================" << std::endl;
	std::cout << "dur time :: " << frame_sec3 << "micro sec" << std::endl;
	tofile_b(output, "../Calc_Validation/output/C_Tensor_concat");
}