// 2021-7-22 by YH PARK

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>
#include<fstream>
using namespace std;
using namespace chrono;

/***************************************************************************
	Conservertive Convolution algotirhm (with zeropadding option)
****************************************************************************/

void zeroPadding(vector<float>& output, vector<float>& input, int IN, int IC, int IH, int IW, int TP, int BP, int LP, int RP) {
	cout << "===== Zero Padding ===== \n";
	
	int C_offset_i, C_offset_o,
		H_offset_i, H_offset_o,
		W_offset_i, W_offset_o,
		⁠g_idx_i, g_idx_o;
	int N_offset_i = IC * IH * IW;
	int N_offset_o = IC * (IH + TP + BP) * (IW + LP + RP);
	for (int ⁠n_idx = 0; ⁠n_idx < IN; ⁠n_idx++){
		C_offset_i = ⁠n_idx * N_offset_i;
		C_offset_o = ⁠n_idx * N_offset_o;
		for (int ⁠c_idx = 0; ⁠c_idx < IC; ⁠c_idx++){
			H_offset_i = ⁠c_idx * IH * IW  + C_offset_i;
			H_offset_o = ⁠c_idx * (IH + TP + BP) * (IW + LP + RP) + C_offset_o;
			for (int ⁠h_idx = 0; ⁠h_idx < IH; ⁠h_idx++){
				W_offset_i = ⁠h_idx * IW + H_offset_i;
				W_offset_o = (⁠h_idx + TP) * (IW + LP + RP) + LP + H_offset_o;
				for (int w_idx = 0; w_idx < IW; w_idx++){
					⁠g_idx_i = w_idx + W_offset_i;
					g_idx_o = w_idx + W_offset_o;
					output[g_idx_o] = input[⁠g_idx_i];
				}
			}
		}
	}
}


void convolution(vector<float>& output, vector<float>& input, vector<float>& weight, int KH, int KW, int stride, int IN, int IC, int IH, int IW, int OC) {
	std::cout << "===== Convolution ===== \n" << std::endl;

	int OH = ((IH - KH) / stride) + 1;
	int OW = ((IW - KW) / stride) + 1;
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
	int OC = 3;
	int IC = 2;
	int IN = 2;
	int IH = 4;
	int IW = 4;
	int KH = 3;
	int KW = 3;
	int TP = 1;
	int BP = 2;
	int LP = 3;
	int RP = 4;

	// weight[OC][lC][KH][KW] 
	// 임시 weight 값 
	vector<float> weight(OC * IC * KH * KW);
	scalarTensor(weight, OC, IC, KH, KW);
	valueCheck(weight, OC, IC, KH, KW, 1);

	// d[IN][IC][IH][IW] 
	// 임시 input 값 
	vector<float> input(IN * IC * IH * IW);
	scalarTensor(input, IN, IC, IH, IW, 0, 1);
	valueCheck(input, IN, IC, IH, IW, 1);

	int stride = 1;
	int OH = ((IH + TP + BP - KH) / stride) + 1;
	int OW = ((IW + LP + RP - KW) / stride) + 1;

	vector<float> output(IN * OC * OH * OW);
	vector<float> output_zeropadding(IN * OC * (IH + TP + BP) * (IW + LP + RP));

	long long start_usec3 = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();

	zeroPadding(output_zeropadding, input, IN, IC, IH, IW, TP, BP, LP, RP);
	valueCheck(output_zeropadding, IN, IC, (IH + TP + BP) , (IW + LP + RP));

	convolution(output, output_zeropadding, weight, KH, KW, stride, IN, IC, (IH + TP + BP), (IW + LP + RP), OC);
	valueCheck(output, IN, OC, OH, OW);

	long long end_usec3 = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
	int frame_sec3 = int(end_usec3 - start_usec3);

	std::cout << "======================================================" << std::endl;
	std::cout << "dur time :: " << frame_sec3 << " [micro sec]" << std::endl;
	tofile(output, "../../output/C_Tensor_zp");
}

