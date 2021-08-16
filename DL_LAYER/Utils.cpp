#include <iostream>
#include <string>
#include <vector>
#include <iomanip> // for setw()
#include <fstream>
#include "Utils.h"
using namespace std;

void Tensor::valueCheck() {
	std::cout << "===== valueCheck func =====" << std::endl;
	int IN, IC, IH, IW;
	if (shape.size() == 4) {
		IN = shape[0];
		IC = shape[1];
		IH = shape[2];
		IW = shape[3];
	}
	else if (shape.size() == 1) {
		IN = shape[0];
		IC = 0;
		IH = 0;
		IW = 0;
	}
	else {
		return;
	}

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
					std::cout << setw(5) << data[g_idx] << " ";
				}std::cout << std::endl;
			}std::cout << std::endl; std::cout << std::endl;
		}
	}
}



//int main()
int utils_test()
{
	int N = 1;
	int C = 2;
	int H = 3;
	int W = 4;

	Tensor t1(N, C, H, W);

	t1.initStep();
	t1.valueCheck();
	

	return 0;
}