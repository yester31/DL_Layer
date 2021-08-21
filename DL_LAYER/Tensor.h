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

class Tensor
{
public:

	Tensor() : totSize(0)
	{}

	Tensor(Tensor &tensor)
	{
		*this = tensor;
	}

	Tensor& operator=(const Tensor &tensor)
	{
		*this = tensor;
	}

	Tensor(int size) : totSize(size)
	{
		shape = { size };
		data.resize(size);
	}

	Tensor(int N, int C, int H, int W) : totSize(N * C * H * W)
	{
		shape = { N,C,H,W };
		data.resize(N * C * H * W);
	}

	void reConstruct(int N, int C, int H, int W)
	{
		shape = { N,C,H,W };
		data.resize(N * C * H * W);
		totSize = N * C * H * W;
	}

	void initStep(float start = 1, float step = 0)
	{
		std::cout << "===== InitTensor func (step)=====" << std::endl;
		float count = start;
		for (int i = 0; i < data.size(); i++) {
			data[i] = count;
			count += step;
		}
	}

	void initScalar(float scalar = 0)
	{
		std::cout << "===== InitTensor func (scalar = " << scalar << ")=====" << std::endl;
		for (int i = 0; i < data.size(); i++) {
			data[i] = scalar;
		}
	}

	void initRandom(float min = -10.f, float max = 10.f)
	{
		std::cout << "===== InitTensor func (random) =====" << std::endl;
		for (int i = 0; i < data.size(); i++) {
			data[i] = min + static_cast <float>(rand()) / (static_cast <float> (RAND_MAX / (max - min)));
		}
	}

	void tofile(string fname = "../Calc_Validation/output/C_Tensor") {
		std::ofstream fs(fname, ios::binary);
		if (fs.is_open())
			fs.write((const char*)data.data(), data.size() * sizeof(float));
		fs.close();
		std::cout << "the output file produced in output folder." << std::endl;
	}

	void valueCheck();

	float* getData() {
		return this->data.data();
	}

	int* getShape() {
		return this->shape.data();
	}

	string getNmae() {
		return this->tensorName;
	}

	uint64_t getTotSize() {
		return this->totSize;
	}

	void setShape(vector<int> shape) {
		this->shape = shape;
		for (int idx=0; idx<shape.size(); idx++) {
			totSize += shape[idx];
		}
		data.resize(totSize);
	}

	void setName(string name) {
		this->tensorName = name;
	}

	~Tensor(){}

private:
	vector<int> shape;
	vector<float> data;
	string tensorName;
	uint64_t totSize;
};


//void valueCheck(vector<float>& Input, int IN = 1, int IC = 1, int IH = 1, int IW = 1, bool one = false) {
//	std::cout << "===== valueCheck func =====" << std::endl;
//	if (one) IN = 1;
//	int tot = IN * IC * IH * IW;
//	if (Input.size() != tot) {
//		if (tot == 1)
//		{
//			IN = Input.size();
//		}
//		else {
//			return;
//		}
//	}
//	int N_offset = IC * IH * IW;
//	int C_offset, H_offset, W_offset, g_idx;
//	for (int ⁠n_idx = 0; ⁠n_idx < IN; ⁠n_idx++) {
//		C_offset = ⁠n_idx * N_offset;
//		for (int ⁠c_idx = 0; ⁠c_idx < IC; ⁠c_idx++) {
//			H_offset = ⁠c_idx * IW * IH + C_offset;
//			for (int ⁠h_idx = 0; ⁠h_idx < IH; ⁠h_idx++) {
//				W_offset = ⁠h_idx * IW + H_offset;
//				for (int w_idx = 0; w_idx < IW; w_idx++) {
//					g_idx = w_idx + W_offset;
//					std::cout << setw(5) << Input[g_idx] << " ";
//				}std::cout << std::endl;
//			}std::cout << std::endl; std::cout << std::endl;
//		}
//	}
//}
//
//void initTensor(vector<float>& output, float start = 1, float step = 0)
//{
//	std::cout << "===== InitTensor func (scalar or step)=====" << std::endl;
//	float count = start;
//	for (int i = 0; i < output.size(); i++) {
//		output[i] = count;
//		count += step;
//	}
//}
//
//void initTensor(vector<float>& output, string random, float min = -10.f, float max = 10.f)
//{
//	std::cout << "===== InitTensor func (random value) =====" << std::endl;
//
//	for (int i = 0; i < output.size(); i++) {
//		output[i] = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
//	}
//}
//
//void scalarTensor(vector<float>& output, int N, int C, int H, int W, float start = 1, float step = 0) {
//	std::cout << "===== scalarTensor func =====" << std::endl;
//	std::cout << "Tensor[" << N << "][" << C << "][" << H << "][" << W << "]" << std::endl << std::endl;
//	int tot_size = N * C * H * W;
//	if (output.size() != tot_size)
//		output.resize(tot_size);
//	initTensor(output, start, step);
//}

//void tofile(vector<float> &Buffer, string fname = "../Calc_Validation/output/C_Tensor") {
//	std::ofstream fs(fname, ios::binary);
//	if (fs.is_open())
//		fs.write((const char*)Buffer.data(), Buffer.size() * sizeof(float));
//	fs.close();
//	std::cout << "the output file produced in output folder." << std::endl;
//}

