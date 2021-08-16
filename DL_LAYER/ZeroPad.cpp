// 2021-7-22 by YH PARK

/***************************************************************************
	Conventional Convolution algotirhm (with zeropadding option)
****************************************************************************/
#include "Utils.h"

void zeroPadding(vector<float>& output, vector<float>& input, int IN, int IC, int IH, int IW, int TP, int BP, int LP, int RP) {
	cout << "===== Zero Padding ===== \n";

	int C_offset_i, C_offset_o,
		H_offset_i, H_offset_o,
		W_offset_i, W_offset_o,
		⁠g_idx_i, g_idx_o;
	int N_offset_i = IC * IH * IW;
	int N_offset_o = IC * (IH + TP + BP) * (IW + LP + RP);
	for (int ⁠n_idx = 0; ⁠n_idx < IN; ⁠n_idx++) {
		C_offset_i = ⁠n_idx * N_offset_i;
		C_offset_o = ⁠n_idx * N_offset_o;
		for (int ⁠c_idx = 0; ⁠c_idx < IC; ⁠c_idx++) {
			H_offset_i = ⁠c_idx * IH * IW + C_offset_i;
			H_offset_o = ⁠c_idx * (IH + TP + BP) * (IW + LP + RP) + C_offset_o;
			for (int ⁠h_idx = 0; ⁠h_idx < IH; ⁠h_idx++) {
				W_offset_i = ⁠h_idx * IW + H_offset_i;
				W_offset_o = (⁠h_idx + TP) * (IW + LP + RP) + LP + H_offset_o;
				for (int w_idx = 0; w_idx < IW; w_idx++) {
					⁠g_idx_i = w_idx + W_offset_i;
					g_idx_o = w_idx + W_offset_o;
					output[g_idx_o] = input[⁠g_idx_i];
				}
			}
		}
	}
}

//void convolution(vector<float>& output, vector<float>& input, vector<float>& weight, int KH, int KW, int stride, int IN, int IC, int IH, int IW, int OC);

//int main()
//{
//	int OC = 3;
//	int IC = 2;
//	int IN = 2;
//	int IH = 4;
//	int IW = 4;
//	int KH = 3;
//	int KW = 3;
//	int TP = 1;
//	int BP = 2;
//	int LP = 3;
//	int RP = 4;
//
//	// weight[OC][lC][KH][KW] 
//	// 임시 weight 값 
//	vector<float> weight(OC * IC * KH * KW);
//	scalarTensor(weight, OC, IC, KH, KW);
//	valueCheck(weight, OC, IC, KH, KW, 1);
//
//	// d[IN][IC][IH][IW] 
//	// 임시 input 값 
//	vector<float> input(IN * IC * IH * IW);
//	scalarTensor(input, IN, IC, IH, IW, 0, 1);
//	valueCheck(input, IN, IC, IH, IW, 1);
//
//	int stride = 1;
//	int OH = ((IH + TP + BP - KH) / stride) + 1;
//	int OW = ((IW + LP + RP - KW) / stride) + 1;
//
//	vector<float> output(IN * OC * OH * OW);
//	vector<float> output_zeropadding(IN * OC * (IH + TP + BP) * (IW + LP + RP));
//
//	long long start_usec3 = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
//
//	zeroPadding(output_zeropadding, input, IN, IC, IH, IW, TP, BP, LP, RP);
//	valueCheck(output_zeropadding, IN, IC, (IH + TP + BP), (IW + LP + RP));
//
//	convolution(output, output_zeropadding, weight, KH, KW, stride, IN, IC, (IH + TP + BP), (IW + LP + RP), OC);
//	valueCheck(output, IN, OC, OH, OW);
//
//	long long end_usec3 = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
//	int frame_sec3 = int(end_usec3 - start_usec3);
//
//	std::cout << "======================================================" << std::endl;
//	std::cout << "dur time :: " << frame_sec3 << " [micro sec]" << std::endl;
//	tofile(output, "../Calc_Validation/output/C_Tensor_zp");
//}
//
