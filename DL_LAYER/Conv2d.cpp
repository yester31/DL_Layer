// 2021-7-22 by YH PARK
// 2021-8-14 update
/***************************************************************************
	Conventional Convolution algotirhm (without any option)
****************************************************************************/
#include "Utils.h"

// layer(functional) class 필요 ***
Tensor convolution(Tensor &inTensor, int KH, int KW, int stride, int OC) {
	
	// 1. weight 존재 유무 체크 없으면 -> 초기화 or 주입(전달)
	Tensor wTensor = Tensor(1,2,3,4);
	// weight 초기화함수 필요 ***


	float* weight = wTensor.getData();

	// 2. input tensor 체크 
	float* input = inTensor.getData();
	int IN = inTensor.getShape()[0];
	int IC = inTensor.getShape()[1];
	int IH = inTensor.getShape()[2];
	int IW = inTensor.getShape()[3];

	// 3. output tenosr 생성
	int OH = ((IH - KH) / stride) + 1;
	int OW = ((IW - KW) / stride) + 1;
	Tensor outTensor(IN, OC, OH, OW);
	float* output = outTensor.getData();

	// 4. 연산 수행 
	std::cout << "===== Convolution ===== \n" << std::endl;

	int C_offset_i, C_offset_o, C_offset_k, H_offset_i, H_offset_o, H_offset_k, W_offset_i, W_offset_o, W_offset_k, ⁠g_idx_i, g_idx_o, g_idx_k;
	int N_offset_i = IC * IH * IW;
	int N_offset_o = OC * OH * OW;
	int N_offset_k = IC * KH * KW;
	for (int ⁠n_idx = 0; ⁠n_idx < IN; ⁠n_idx++) {
		C_offset_i = ⁠n_idx * N_offset_i;
		C_offset_o = ⁠n_idx * N_offset_o;
		for (int k_idx = 0; k_idx < OC; k_idx++) {
			C_offset_k = k_idx * N_offset_k;
			H_offset_o = k_idx * OH * OW + C_offset_o;
			for (int ⁠c_idx = 0; ⁠c_idx < IC; ⁠c_idx++) {
				H_offset_i = ⁠c_idx * IH * IW + C_offset_i;
				H_offset_k = ⁠c_idx * KH * KW + C_offset_k;
				for (int rowStride = 0; rowStride < OH; rowStride++) {
					W_offset_o = rowStride * OW + H_offset_o;
					for (int colStride = 0; colStride < OW; colStride++) {
						float sum = 0;
						g_idx_o = colStride + W_offset_o;
						for (int y = rowStride * stride; y < rowStride * stride + KH; y++) {
							W_offset_i = y * IW + H_offset_i;
							W_offset_k = (y - rowStride * stride) * KH + H_offset_k;
							for (int x = colStride * stride; x < colStride * stride + KW; x++) {
								⁠g_idx_i = x + W_offset_i;
								g_idx_k = (x - colStride * stride) + W_offset_k;
								sum += input[⁠g_idx_i] * weight[g_idx_k];
							}
						}
						output[g_idx_o] += sum;
					}
				}
			}
		}
	}
	return outTensor;
}

void convolution(vector<float>& output, vector<float>& input, vector<float>& weight, int KH, int KW, int stride, int IN, int IC, int IH, int IW, int OC) {
	int OH = ((IH - KH) / stride) + 1;
	int OW = ((IW - KW) / stride) + 1;
	std::cout << "===== Convolution ===== \n" << std::endl;

	int C_offset_i, C_offset_o, C_offset_k,
		H_offset_i, H_offset_o, H_offset_k,
		W_offset_i, W_offset_o, W_offset_k,
		⁠g_idx_i, g_idx_o, g_idx_k;
	int N_offset_i = IC * IH * IW;
	int N_offset_o = OC * OH * OW;
	int N_offset_k = IC * KH * KW;
	for (int ⁠n_idx = 0; ⁠n_idx < IN; ⁠n_idx++) {
		C_offset_i = ⁠n_idx * N_offset_i;
		C_offset_o = ⁠n_idx * N_offset_o;
		for (int k_idx = 0; k_idx < OC; k_idx++) {
			C_offset_k = k_idx * N_offset_k;
			H_offset_o = k_idx * OH * OW + C_offset_o;
			for (int ⁠c_idx = 0; ⁠c_idx < IC; ⁠c_idx++) {
				H_offset_i = ⁠c_idx * IH * IW + C_offset_i;
				H_offset_k = ⁠c_idx * KH * KW + C_offset_k;
				for (int rowStride = 0; rowStride < OH; rowStride++) {
					W_offset_o = rowStride * OW + H_offset_o;
					for (int colStride = 0; colStride < OW; colStride++) {
						float sum = 0;
						g_idx_o = colStride + W_offset_o;
						for (int y = rowStride * stride; y < rowStride * stride + KH; y++) {
							W_offset_i = y * IW + H_offset_i;
							W_offset_k = (y - rowStride * stride) * KH + H_offset_k;
							for (int x = colStride * stride; x < colStride * stride + KW; x++) {
								⁠g_idx_i = x + W_offset_i;
								g_idx_k = (x - colStride * stride) + W_offset_k;
								sum += input[⁠g_idx_i] * weight[g_idx_k];
							}
						}
						output[g_idx_o] += sum;
					}
				}
			}
		}
	}
}


//int main()
//{
//	int OC = 3;
//	int IC = 2;
//	int IN = 2;
//	int IH = 4;
//	int IW = 4;
//	int KH = 3;
//	int KW = 3;
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
//	int OH = ((IH - KH) / stride) + 1;
//	int OW = ((IW - KW) / stride) + 1;
//
//	vector<float> output(IN * OC * OH * OW);
//
//	long long start_usec3 = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
//
//	convolution(output, input, weight, KH, KW, stride, IN, IC, IH, IW, OC);
//	valueCheck(output, IN, OC, OH, OW);
//
//	long long end_usec3 = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
//	int frame_sec3 = int(end_usec3 - start_usec3);
//
//	std::cout << "======================================================" << std::endl;
//	std::cout << "dur time :: " << frame_sec3 << "micro sec" << std::endl;
//	tofile(output);
//}

