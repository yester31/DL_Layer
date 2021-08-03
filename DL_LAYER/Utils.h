#pragma once
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

template <typename T>
void valueCheck(vector<T>& Input, int IN = 1, int IC = 1, int IH = 1, int IW = 1, bool one = false) {
	std::cout << "===== valueCheck func =====" << std::endl;
	if (one) IN = 1;
	int tot = IN * IC * IH * IW;
	if (Input.size() != tot) {
		if (tot == 1)
		{
			IN = Input.size();
		}
		else {
			return;
		}
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
					std::cout << setw(5) << Input[g_idx] << " ";
				}std::cout << std::endl;
			}std::cout << std::endl; std::cout << std::endl;
		}
	}
}

template <typename T>
void initTensor(vector<T>& output, T start = 1, T step = 0)
{
	std::cout << "===== InitTensor func =====" << std::endl;
	T count = start;
	for (int i = 0; i < output.size(); i++) {
		output[i] = count;
		count += step;
	}
}

template <typename T>
void scalarTensor(vector<T>& output, int N, int C, int H, int W, T start = 1, T step = 0) {
	std::cout << "===== scalarTensor func =====" << std::endl;
	std::cout << "Tensor[" << N << "][" << C << "][" << H << "][" << W << "]" << std::endl << std::endl;
	int tot_size = N * C * H * W;
	if (output.size() != tot_size)
		output.resize(tot_size);
	initTensor(output, start, step);
}

template <typename T>
void tofile(vector<T> &Buffer, string fname = "../../Calc_Validation/output/C_Tensor") {
	std::ofstream fs(fname, ios::binary);
	if (fs.is_open())
		fs.write((const char*)Buffer.data(), Buffer.size() * sizeof(T));
	fs.close();
	std::cout << "the output file produced in output folder." << std::endl;
}